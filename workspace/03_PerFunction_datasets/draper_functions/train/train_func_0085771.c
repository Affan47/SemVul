___device_release
   ___P((___device *self),
        (self)
___device *self;)
{
  ___SCMOBJ e = ___FIX(___NO_ERR);

  if (
#ifdef USE_PUMPS
      InterlockedDecrement (&self->refcount) == 0
#else
      --self->refcount == 0
#endif
      )
    {
      e = ___device_release_virt (self);
      ___free_mem (self);
    }

  return e;
}
