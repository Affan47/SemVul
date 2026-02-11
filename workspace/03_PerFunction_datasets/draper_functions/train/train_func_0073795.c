ReplaceTargetState (LCTree_t *LCTree, int local_root, int state, int motherstate)


{
   int i;

   for (i = 0; i < MAXLABELS; i++)
   {
      tlist_t** pointer = &(LCTree->states [local_root].tree_out [i]);
      tlist_t*  pos = LCTree->states [local_root].tree_out [i];
      int	counter = 0;


      while (pos)
      {
	 if (pos->value == state)
	 {
	    tlist_t *tmp = pos->next;
	    counter += pos->count;
	    *pointer = pos->next;
	    fiasco_free (pos);
	    pos = tmp;
	 }
	 else
	 {
	    pointer = &pos->next;
	    pos     = pos->next;
	 }
      }


      if (counter > 0)
	 InsertDesList (&(LCTree->states [local_root].tree_out [i]), motherstate,
			counter);

   }


   for (i = 0; i < MAXLABELS; i++)
      if (ischild (LCTree->states [local_root].child[i]))
	 ReplaceTargetState (LCTree, LCTree->states [local_root].child [i],
			     state, motherstate);
}
