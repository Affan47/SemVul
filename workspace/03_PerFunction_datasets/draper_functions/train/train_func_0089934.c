CreateSubsecWorker(subsec_t *sub, superblock_t *block)
{
  int num;

  while (block->segs)
  {

    seg_t *cur = block->segs;
    block->segs = cur->next;


    cur->next = sub->seg_list;
    cur->block = NULL;

    sub->seg_list = cur;
  }


  for (num=0; num < 2; num++)
  {
    superblock_t *A = block->subs[num];

    if (A)
    {
      CreateSubsecWorker(sub, A);

      if (A->real_num + A->mini_num > 0)
        InternalError("CreateSubsec: child %d not empty !", num);

      FreeSuper(A);
      block->subs[num] = NULL;
    }
  }

  block->real_num = block->mini_num = 0;
}
