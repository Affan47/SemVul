pdb_read_rec(pdbfile *fin, gbuint8 *flags, gbuint8 *category, gbuint32 *rec_id, void **data)
{
  if (pdb_eof(fin)) {
    return -1;
  } else {
    pdbrec_t *rec = fin->rec_curr;
    fin->rec_curr = rec->next;

    if (data) {
      *data = rec->data;
    }
    if (flags) {
      *flags = rec->flags;
    }
    if (category) {
      *category = rec->category;
    }
    if (rec_id) {
      *rec_id = rec->id;
    }

    return rec->size;
  }
}
