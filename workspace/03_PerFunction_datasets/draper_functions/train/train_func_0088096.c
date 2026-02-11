sanity_check_size(size_t size, const char *called_as,
			      int line, const char *file)
{


  if (size == 0) {
    log_verbose("Warning: %s with size %lu at line %d of %s",
                called_as, (unsigned long) size, line, file);
  }
}
