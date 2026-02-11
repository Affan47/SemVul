vbo_print_vertex_list(struct gl_context *ctx, void *data)
{
   struct vbo_save_vertex_list *node = (struct vbo_save_vertex_list *) data;
   GLuint i;
   (void) ctx;

   printf("VBO-VERTEX-LIST, %u vertices %d primitives, %d vertsize\n",
          node->count, node->prim_count, node->vertex_size);

   for (i = 0; i < node->prim_count; i++) {
      struct _mesa_prim *prim = &node->prim[i];
      printf("   prim %d: %s%s %d..%d %s %s\n",
             i,
             _mesa_lookup_prim_by_nr(prim->mode),
             prim->weak ? " (weak)" : "",
             prim->start,
             prim->start + prim->count,
             (prim->begin) ? "BEGIN" : "(wrap)",
             (prim->end) ? "END" : "(wrap)");
   }
}
