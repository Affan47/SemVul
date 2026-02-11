draw_compute_vertex_size(struct vertex_info *vinfo)
{
   uint i;

   vinfo->size = 0;
   for (i = 0; i < vinfo->num_attribs; i++)
      vinfo->size += draw_translate_vinfo_size(vinfo->attrib[i].emit);

   assert(vinfo->size % 4 == 0);

   vinfo->size /= 4;
}
