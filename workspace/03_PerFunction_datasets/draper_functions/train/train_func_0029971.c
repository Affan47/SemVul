VTGen_get_buflevel(VTGen* gen)
{
  VTGEN_CHECK(gen);

  return (uint8_t)(((gen->buf->pos - gen->buf->mem) * 100) / gen->buf->size);
}
