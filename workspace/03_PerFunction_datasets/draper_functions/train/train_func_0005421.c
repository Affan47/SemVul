pdb_write_rec(pdbfile *fout, const gbuint8 flags, const gbuint8 category, const gbuint32 rec_id, const void *data, const gbuint32 size)
{
  pdbrec_t *rec, *cur;

  rec = (pdbrec_t*) xcalloc(1, sizeof(*rec));
  rec->category = category;
  rec->flags = category;
  rec->id = rec_id;
  rec->size = size;
  if (size > 0) {
    rec->data = (char*) xmalloc(size);
    memcpy(rec->data, data, size);
  }


  cur = fout->rec_list;
  if (cur == NULL) {
    fout->rec_list = rec;
  } else {
    pdbrec_t *prev = NULL;

    while (cur) {
      if (rec_id < cur->id) {
        rec->next = cur;
        if (prev == NULL) {
          fout->rec_list = rec;
        } else {
          prev->next = rec;
        }
        break;
      } else if (rec_id == cur->id) {
        rec->next = cur->next;
        if (prev == NULL) {
          fout->rec_list = rec;
        } else {
          prev->next = rec;
        }
        if (cur->data) {
          xfree(cur->data);
        }
        xfree(cur);
        cur = rec;
        break;
      }
      prev = cur;
      cur = cur->next;
    }
    if (! cur) {
      if (prev == NULL) {
        fout->rec_list = rec;
      } else {
        prev->next = rec;
      }
    }
  }
  fout->rec_ct++;
}
