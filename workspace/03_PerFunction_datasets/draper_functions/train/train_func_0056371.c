key_upsize(ESL_KEYHASH *kh)
{
  void     *p;
  int       i;
  uint32_t  val;
  int       status;


  if (kh->hashsize >= (1<<28)) return eslOK;


  ESL_RALLOC(kh->hashtable, p, sizeof(int) * (kh->hashsize << 3));
  kh->hashsize  = kh->hashsize << 3;
  for (i = 0; i < kh->hashsize; i++) kh->hashtable[i] = -1;


  for (i = 0; i < kh->nkeys; i++)
    {
      val                = jenkins_hash(kh->smem + kh->key_offset[i], -1, kh->hashsize);
      kh->nxt[i]         = kh->hashtable[val];
      kh->hashtable[val] = i;
    }
  return eslOK;

 ERROR:
  return eslEMEM;
}
