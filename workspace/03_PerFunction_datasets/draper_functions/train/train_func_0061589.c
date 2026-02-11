cond_init (ACE_cond_t *cv, short type, const char *name, void *arg)
{
  ACE_condattr_t attributes;
  if (ACE_OS::condattr_init (attributes, type) == 0
      && ACE_OS::cond_init (cv, attributes, name, arg) == 0)
    {
      (void) ACE_OS::condattr_destroy (attributes);
      return 0;
    }
  return -1;
}
