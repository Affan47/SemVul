secure_free (void *ptr, size_t len)
{
  assert (len);

  if (ptr)
    {
      secure_memset (ptr, '\0', len);
#if defined(MAP_ANONYMOUS) && defined(MAP_LOCK) && HAVE_MMAP

      munmap (ptr, len);
#elif defined(MAP_ANONYMOUS) && !defined(MAP_LOCK)


      munmap (ptr, len);
#else
      free (ptr);
#endif
    }
}
