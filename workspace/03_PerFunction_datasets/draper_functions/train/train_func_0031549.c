key_debug(struct brw_context *brw, const char *name, int a, int b)
{
   if (a != b) {
      perf_debug("  %s %d->%d\n", name, a, b);
      return true;
   }
   return false;
}
