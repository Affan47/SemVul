gst_dmabuf_mem_share (GstMemory * gmem, gssize offset, gssize size)
{
#ifdef HAVE_MMAP
  GstDmaBufMemory *mem = (GstDmaBufMemory *) gmem;
  GstDmaBufMemory *sub;
  GstMemory *parent;

  GST_DEBUG ("%p: share %" G_GSSIZE_FORMAT " %" G_GSIZE_FORMAT, mem, offset,
      size);


  if ((parent = mem->mem.parent) == NULL)
    parent = (GstMemory *) mem;

  if (size == -1)
    size = gmem->maxsize - offset;

  sub = g_slice_new0 (GstDmaBufMemory);

  gst_memory_init (GST_MEMORY_CAST (sub), GST_MINI_OBJECT_FLAGS (parent) |
      GST_MINI_OBJECT_FLAG_LOCK_READONLY, mem->mem.allocator, parent,
      mem->mem.maxsize, mem->mem.align, mem->mem.offset + offset, size);

  sub->fd = dup (mem->fd);
  g_mutex_init (&sub->lock);

  return GST_MEMORY_CAST (sub);
#else
  return NULL;
#endif
}
