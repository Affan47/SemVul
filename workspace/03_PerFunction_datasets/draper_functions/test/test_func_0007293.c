pick (leaf *head, short ply)


{
   int best;
   leaf *p, *pbest, tmp;

   best = head->score;
   pbest = head;
   for (p = head+1; p < TreePtr[ply+1]; p++)
   {
      if (p->score > best)
      {
         pbest = p;
	 best = p->score;
      }
   }


   tmp = *head;
   *head = *pbest;
   *pbest = tmp;
}
