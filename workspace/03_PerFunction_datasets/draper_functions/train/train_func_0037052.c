show_heap (FILE_T f, NODE_T * p, A68_HANDLE * z, int top, int n)
{
  int k = 0, m = n, sum = 0;
  (void) p;
  ASSERT (snprintf (output_line, SNPRINTF_SIZE, "size=%d available=%d garbage collections=%d", heap_size, heap_available (), garbage_collects) >= 0);
  WRITELN (f, output_line);
  for (; z != NO_HANDLE; FORWARD (z), k++) {
    if (n > 0 && sum <= top) {
      n--;
      indent_crlf (f);
      ASSERT (snprintf (output_line, SNPRINTF_SIZE, "heap(%p+%d) %s", POINTER (z), SIZE (z), moid_to_string (MOID (z), MOID_WIDTH, NO_NODE)) >= 0);
      WRITE (f, output_line);
      sum += SIZE (z);
    }
  }
  ASSERT (snprintf (output_line, SNPRINTF_SIZE, "printed %d out of %d handles", m, k) >= 0);
  WRITELN (f, output_line);
}
