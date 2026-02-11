myDeallocateFunction (void *ptr, size_t size)
{


  int bn=bufNum(size);
  if(bn!=-1)return theBucketList[bn].free(ptr);
  return free(ptr);
}
