_ds_get_nexttoken (DSPAM_CTX * CTX)
{
  struct _hash_drv_storage *s = (struct _hash_drv_storage *) CTX->storage;
  struct _hash_drv_spam_record rec;
  struct _ds_storage_record *sr;
  struct _ds_spam_stat stat;

  rec.hashcode = 0;

  sr = calloc(1, sizeof(struct _ds_storage_record));
  if (!sr) {
    LOG(LOG_CRIT, ERR_MEM_ALLOC);
    return NULL;
  }

  if (s->offset_nexttoken == 0) {
    s->offset_header = s->map->addr;
    s->offset_nexttoken = sizeof(struct _hash_drv_header);
    memcpy(&rec,
           (void *)((unsigned long) s->map->addr + s->offset_nexttoken),
           sizeof(struct _hash_drv_spam_record));
    if (rec.hashcode)
      _ds_get_spamrecord (CTX, rec.hashcode, &stat);
  }

  while(rec.hashcode == 0 ||
   ((unsigned long) s->map->addr + s->offset_nexttoken ==
    (unsigned long) s->offset_header + sizeof(struct _hash_drv_header) +
    (s->offset_header->hash_rec_max * sizeof(struct _hash_drv_spam_record))))
  {
    s->offset_nexttoken += sizeof(struct _hash_drv_spam_record);

    if ((unsigned long) s->map->addr + s->offset_nexttoken >
        (unsigned long) s->offset_header + sizeof(struct _hash_drv_header) +
      (s->offset_header->hash_rec_max * sizeof(struct _hash_drv_spam_record)))
    {
      if (s->offset_nexttoken < s->map->file_len) {
        s->offset_header = (void *)((unsigned long) s->map->addr +
          (s->offset_nexttoken - sizeof(struct _hash_drv_spam_record)));

        s->offset_nexttoken += sizeof(struct _hash_drv_header);
        s->offset_nexttoken -= sizeof(struct _hash_drv_spam_record);
      } else {
        free(sr);
        return NULL;
      }
    }

    memcpy(&rec,
           (void *)((unsigned long) s->map->addr + s->offset_nexttoken),
           sizeof(struct _hash_drv_spam_record));
    _ds_get_spamrecord (CTX, rec.hashcode, &stat);
  }

  sr->token = rec.hashcode;
  sr->spam_hits = stat.spam_hits;
  sr->innocent_hits = stat.innocent_hits;
  sr->last_hit = time(NULL);
  return sr;
}
