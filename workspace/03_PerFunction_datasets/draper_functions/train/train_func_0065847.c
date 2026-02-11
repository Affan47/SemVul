ibuf_write(Ibuffer ibuf, int i)
{
  if (ibuf->write_position >= ibuf->size) {
    int size2 = ibuf->size * 2;
    int *buf2, i;
    printf("ibuf_write, increasing buf size from %d to %d\n",
	   ibuf->size, size2);
    buf2 = malloc(size2 * sizeof(int));
    for (i = 0; i < ibuf->size; i++)
      buf2[i] = ibuf->buf[i];
    free(ibuf->buf);
    ibuf->buf = buf2;
    ibuf->size = size2;
  }
  ibuf->buf[ibuf->write_position] = i;
  ibuf->write_position++;
}
