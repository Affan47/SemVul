draw_alloc_temp_verts( struct draw_stage *stage, unsigned nr )
{
   assert(!stage->tmp);

   stage->tmp = NULL;
   stage->nr_tmps = nr;

   if (nr != 0)
   {
      unsigned i;
      ubyte *store = (ubyte *) MALLOC( MAX_VERTEX_SIZE * nr );

      if (store == NULL)
         return FALSE;

      stage->tmp = (struct vertex_header **) MALLOC( sizeof(struct vertex_header *) * nr );
      if (stage->tmp == NULL) {
         FREE(store);
         return FALSE;
      }

      for (i = 0; i < nr; i++)
         stage->tmp[i] = (struct vertex_header *)(store + i * MAX_VERTEX_SIZE);
   }

   return TRUE;
}
