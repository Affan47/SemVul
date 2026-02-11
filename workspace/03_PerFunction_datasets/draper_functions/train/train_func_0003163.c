___device_tty_force_output_raw_virt
   ___P((___device_stream *self,
         int level),
        (self,
         level)
___device_stream *self;
int level;)
{
  ___device_tty *d = ___CAST(___device_tty*,self);

#ifdef USE_LINEEDITOR

  if (d->stage >= TTY_STAGE_INIT_DONE)
    return lineeditor_output_drain (d);

#endif

  return ___FIX(___NO_ERR);
}
