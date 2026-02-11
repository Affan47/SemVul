MPCreateTrack(line, file)
int line;
char *file;
{
  MemPool mp;
  struct pool *pool;
#ifdef TRACKER
  struct track *f;
#endif

#ifndef MPDEBUG
  pool = create_pool(sizeof(struct MemPoolP));
  if (pool == NULL) return(NULL);
  mp = (MemPool)use_pool(pool, sizeof(struct MemPoolP));
  myassert(mp != NULL, "MPCreate: use_pool failed!");
  mp->plist = pool;
  mp->len = pool->len;
#else
  mp = (MemPool)malloc(sizeof(struct MemPoolP));
  if (mp == NULL) return(NULL);
  memset(mp, 0, sizeof(struct MemPoolP));
#endif

#ifdef TRACKER
  f = (struct track *)malloc(sizeof(struct track));
  if (f == NULL) abort();
  f->mp = mp;
  f->line = line;
  f->file = file;
  f->next = track_list;
  track_list = f;
#endif

  return(mp);
}
