search_fastpath_emit( struct tnl_clipspace *vtx )
{
   struct tnl_clipspace_fastpath *fp = vtx->fastpath;

   for ( ; fp ; fp = fp->next) {
      if (match_fastpath(vtx, fp)) {
         vtx->emit = fp->func;
	 return GL_TRUE;
      }
   }

   return GL_FALSE;
}
