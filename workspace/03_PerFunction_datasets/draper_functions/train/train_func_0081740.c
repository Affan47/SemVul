chunk_get_prev_nc(chunk_t *cur, chunk_nav_t nav)
{
   chunk_t *pc = cur;

   do
   {
      pc = chunk_get_prev(pc, nav);
   } while ((pc != NULL) && chunk_is_comment(pc));
   return(pc);
}
