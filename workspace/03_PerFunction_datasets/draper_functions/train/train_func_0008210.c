buffer_new_with_copy(char *str) {
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self) return NULL;
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}
