searchBucketFor(MSHashEntry *entry_,const char *key_) const
{
  while (entry_!=0)
   {
     if (strcmp(entry_->stringKey(),key_)==0) return entry_;
     entry_=entry_->next();
   }
  return entry_;
}
