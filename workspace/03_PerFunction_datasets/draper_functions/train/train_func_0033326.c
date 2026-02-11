Find(const char* className)
{
  unsigned long bucket = this->Hash(className);

  unsigned int i;
  for(i=0; i < this->BucketCounts[bucket];++i)
    {
    if(strcmp(this->Buckets[bucket][i].GetClassName(), className) == 0)
      { return this->Buckets[bucket][i].GetFunction(); }
    }
  return 0;
}
