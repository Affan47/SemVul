Check_Overlap_DD (ISNS_DD_LIST p_dlist_src, ISNS_DD_LIST p_dlist_node)
{
   int ii, jj;

   for (ii = 0; ii < MAX_DD_PER_LIST; ii++)
   {
      if (p_dlist_src[ii]==0)
         break;

      for (jj = 0; jj < MAX_DD_PER_LIST; jj++)
      {
         if (p_dlist_node[jj]==0)
            break;

         if (p_dlist_src[ii] == p_dlist_node[jj])
            return (TRUE);
      }
   }

   return (FALSE);
}
