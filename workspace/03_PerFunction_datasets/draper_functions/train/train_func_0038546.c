deduce_magic(void *sf, int32 extent)
{
 int i;
 for(i=0;magic[i].magic;i++)
 if (extent >= magic[i].len && memcmp(magic[i].magic,sf,magic[i].len)==0)
  return magic[i].name;
 return NULL;
}
