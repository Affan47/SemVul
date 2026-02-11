ring_alloc (size_t initial_size, size_t bpl, size_t ppl)
{
  ring_buffer *rb;
  uint8_t *buff;

  if ((rb = (ring_buffer *)malloc(sizeof(*rb))) == NULL)
    return NULL;
  if ((buff = (uint8_t *)malloc(initial_size * sizeof(*buff))) == NULL) {
    free(rb);
    return NULL;
  }
  rb->base = buff;
  rb->size = initial_size;
  rb->initial_size = initial_size;

  rb->bpl = bpl;
  rb->ppl = ppl;

  rb->tail_red   = 0;
  rb->tail_green = 1;
  rb->tail_blue  = 2;
  rb->head_complete = 0;

  rb->red_extra   = 0;
  rb->green_extra = 0;
  rb->blue_extra  = 0;
  rb->complete_count = 0;

  return rb;
}
