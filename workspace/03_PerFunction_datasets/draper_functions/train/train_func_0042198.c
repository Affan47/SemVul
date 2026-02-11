vbo_can_merge_prims(const struct _mesa_prim *p0, const struct _mesa_prim *p1)
{
   if (!p0->begin ||
       !p1->begin ||
       !p0->end ||
       !p1->end)
      return false;


   if (p0->mode != p1->mode)
      return false;


   if (p0->start + p0->count != p1->start)
      return false;

   if (p0->basevertex != p1->basevertex ||
       p0->num_instances != p1->num_instances ||
       p0->base_instance != p1->base_instance)
      return false;


   if (p0->mode == GL_POINTS)
      return true;


   if (p0->mode == GL_LINES && p0->count % 2 == 0 && p1->count % 2 == 0)
      return true;


   if (p0->mode == GL_TRIANGLES && p0->count % 3 == 0 && p1->count % 3 == 0)
      return true;


   if (p0->mode == GL_QUADS && p0->count % 4 == 0 && p1->count % 4 == 0)
      return true;

   return false;
}
