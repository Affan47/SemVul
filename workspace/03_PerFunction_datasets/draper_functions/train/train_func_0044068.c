m_pr_su_prefix_err()


{
   struct lk_list *lklp;

   if (curr_m->l_name_prefix[0] != '\0')

   {
      printf("\nconf: M names must be single part");
      return(CSL_ERR);
   }
   lklp = curr_m->pred_list;
   while (lklp != NULL)
   {

      if ((lklp->curr_node->l_name_prefix[0] != '\0') &&
	  (strcmp(lklp->curr_node->l_name_prefix, curr_m->l_name) != 0))
      {
	 printf("\nconf: F name prefix must be the logical name of unique succ");
	 return(CSL_ERR);
      }
      lklp = lklp->next;
   }
   lklp = curr_m->succ_list;
   while (lklp != NULL)
   {

      if ((lklp->curr_node->l_name_prefix[0] != '\0') &&
	  (strcmp(lklp->curr_node->l_name_prefix, curr_m->l_name) != 0))
      {
	 printf("\nconf: F name prefix must be the logical name of unique pred");
	 return(CSL_ERR);
      }
      lklp = lklp->next;
   }
   return 0;
}
