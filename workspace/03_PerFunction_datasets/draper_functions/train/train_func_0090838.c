at_quick_exit (void (*func) (void))
{
  return __cxa_at_quick_exit ((void (*) (void *)) func,
			      &__dso_handle == NULL ? NULL : __dso_handle);
}
