da_resize (struct darray * arr, size_t size)
{
  if (arr->len + 1 < size)
    {
      arr->size = size;
      arr->content = XREALLOC (arr->content, void *, arr->size);
    }
}
