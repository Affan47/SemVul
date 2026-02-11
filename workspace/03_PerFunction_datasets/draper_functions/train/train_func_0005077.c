tag_new_fraction_region (FttCell * cell, TagPar * p)
{
  if (GFS_VALUE (cell, p->v) == 0. && GFS_VALUE (cell, p->c) > THRESHOLD) {
    GtsFifo * fifo = gts_fifo_new ();

    GFS_VALUE (cell, p->v) = ++p->tag;
    gts_fifo_push (fifo, cell);
    while ((cell = gts_fifo_pop (fifo)))
      tag_cell_fraction (fifo, cell, p->c, p->v, p->tag);
    gts_fifo_destroy (fifo);
  }
}
