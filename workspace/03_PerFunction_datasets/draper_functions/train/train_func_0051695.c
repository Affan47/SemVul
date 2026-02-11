___device_tty_width_virt
   ___P((___device_stream *self),
        (self)
___device_stream *self;)
{
  ___device_tty *d = ___CAST(___device_tty*,self);
  ___SCMOBJ e;

  if ((e = ___device_tty_force_open (d)) != ___FIX(___NO_ERR))
    return e;

  if ((e = ___device_tty_update_size (d)) == ___FIX(___NO_ERR))
    return ___FIX(d->terminal_nb_cols);

  return e;
}
