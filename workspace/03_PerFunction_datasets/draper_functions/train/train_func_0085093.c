pack_seq2r2g2b_data(Microtek_Scanner *s, size_t nlines)
{
  SANE_Status status;
  ring_buffer *rb = s->rb;
  size_t nbytes = nlines * rb->bpl;

  size_t start = (rb->head_complete + rb->complete_count) % rb->size;
  size_t max_xfer =
    (start < rb->head_complete) ?
    (rb->head_complete - start) :
    (rb->size - start + rb->head_complete);
  size_t length = MIN(nbytes, max_xfer);

  if (nbytes > max_xfer) {
    DBG(23, "pack_2r2g2b: must expand ring, %lu + %lu\n",
	(u_long)rb->size, (u_long)(nbytes - max_xfer));
    status = ring_expand(rb, (nbytes - max_xfer));
    if (status != SANE_STATUS_GOOD) return status;
  }
  {
    unsigned int line;
    int p;
    size_t pos = start;
    SANE_Byte *sb = s->scsi_buffer;
    SANE_Byte *db = rb->base;

    for (line = 0; line < nlines; line++) {
      for (p = 0; p < s->dest_ppl; p += 2){

	db[pos] = sb[0];
	if (++pos >= rb->size) pos = 0;
	db[pos] = sb[2];
	if (++pos >= rb->size) pos = 0;
	db[pos] = sb[4];
	if (++pos >= rb->size) pos = 0;

	db[pos] = sb[1];
	if (++pos >= rb->size) pos = 0;
	db[pos] = sb[3];
	if (++pos >= rb->size) pos = 0;
	db[pos] = sb[5];
	if (++pos >= rb->size) pos = 0;
	sb += 6;
      }
    }
  }
  rb->complete_count += length;
  return SANE_STATUS_GOOD;
}
