del_best_node(tm_prob *tm)
{
   bc_node **list = tm->samephase_cand;
   int size = tm->samephase_candnum;
   bc_node *temp = NULL, *best_node;
   int pos, ch;
   int rule = tm->par.node_selection_rule;

   if (size == 0)
      return(NULL);

   best_node = list[1];

   temp = list[1] = list[size];

   tm->samephase_candnum = --size;

   if (tm->par.verbosity > 10)
      if (tm->samephase_candnum % 10 == 0)
	 printf("\nTM: tree size: %i , %i\n\n",
		tm->samephase_candnum, tm->nextphase_candnum);

   pos = 1;
   while ((ch=2*pos) < size){
      if (node_compar(tm, rule, list[ch], list[ch+1]))
	 ch++;
      if (node_compar(tm, rule, list[ch], temp)){
	 list[pos] = temp;
	 return(best_node);
      }
      list[pos] = list[ch];
      pos = ch;
   }
   if (ch == size){
      if (node_compar(tm, rule, temp, list[ch])){
	 list[pos] = list[ch];
	 pos = ch;
      }
   }
   list[pos] = temp;
   return(best_node);
}
