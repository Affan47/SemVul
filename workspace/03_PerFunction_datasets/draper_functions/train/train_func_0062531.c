BufferCell_create(size_t size, unsigned char *data) {
  BufferCell *buffer_cell = (BufferCell *)malloc(sizeof(BufferCell));
  if (!buffer_cell) {
    return 0;
  }

  buffer_cell->size = size;
  buffer_cell->data = (unsigned char *)malloc(size);
  if (!buffer_cell->data) {
    free(buffer_cell);
    return 0;
  }

  memcpy(buffer_cell->data, data, size);

  return buffer_cell;
}
