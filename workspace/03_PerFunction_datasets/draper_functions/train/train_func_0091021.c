prim_point(struct draw_assembler *asmblr,
           unsigned idx)
{
   unsigned indices[1];

   if (asmblr->needs_primid) {
      inject_primid(asmblr, idx, asmblr->primid++);
   }
   indices[0] = idx;

   copy_verts(asmblr, indices, 1);
}
