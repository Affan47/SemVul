draw_pt_emit(struct pt_emit *emit,
             const struct draw_vertex_info *vert_info,
             const struct draw_prim_info *prim_info)
{
   const float (*vertex_data)[4] = (const float (*)[4])vert_info->verts->data;
   unsigned vertex_count = vert_info->count;
   unsigned stride = vert_info->stride;
   const ushort *elts = prim_info->elts;
   struct draw_context *draw = emit->draw;
   struct translate *translate = emit->translate;
   struct vbuf_render *render = draw->render;
   unsigned start, i;
   void *hw_verts;


   draw_do_flush( draw, DRAW_FLUSH_BACKEND );

   if (vertex_count == 0)
      return;


   draw->render->set_primitive(draw->render, emit->prim);

   render->allocate_vertices(render,
                             (ushort)translate->key.output_stride,
                             (ushort)vertex_count);

   hw_verts = render->map_vertices( render );
   if (!hw_verts) {
      debug_warn_once("map of vertex buffer failed (out of memory?)");
      return;
   }

   translate->set_buffer(translate,
			 0,
			 vertex_data,
			 stride,
			 ~0);

   translate->set_buffer(translate,
			 1,
			 &draw->rasterizer->point_size,
			 0,
			 ~0);


   translate->run(translate,
		  0,
		  vertex_count,
                  draw->start_instance,
                  draw->instance_id,
		  hw_verts );

   render->unmap_vertices(render, 0, vertex_count - 1);

   for (start = i = 0;
        i < prim_info->primitive_count;
        start += prim_info->primitive_lengths[i], i++)
   {
      render->draw_elements(render,
                            elts + start,
                            prim_info->primitive_lengths[i]);
   }

   render->release_vertices(render);
}
