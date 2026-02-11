mem_info_numvar(int type, int list)
#endif
{
   if ( list < 0 || list >= MEM_CONNECT_MAX_LISTS )
     return 0l;
   if ( !mem_switched_on || type < 0
       || type >= mem_connect[list].ntypes
       || mem_connect[list].free_funcs[type] == NULL )
     return 0l;

   return mem_connect[list].info_sum[type].numvar;
}
