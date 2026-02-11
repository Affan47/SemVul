___os_device_tty_mode_set
   ___P((___SCMOBJ dev,
         ___SCMOBJ input_allow_special,
         ___SCMOBJ input_echo,
         ___SCMOBJ input_raw,
         ___SCMOBJ output_raw,
         ___SCMOBJ speed),
        (dev,
         input_allow_special,
         input_echo,
         input_raw,
         output_raw,
         speed)
___SCMOBJ dev;
___SCMOBJ input_allow_special;
___SCMOBJ input_echo;
___SCMOBJ input_raw;
___SCMOBJ output_raw;
___SCMOBJ speed;)
{
  ___device_tty *d =
    ___CAST(___device_tty*,___FIELD(dev,___FOREIGN_PTR));
  ___SCMOBJ e;

  if ((e = ___device_tty_force_open (d)) == ___FIX(___NO_ERR))
    e = ___device_tty_mode_set
          (d,
           !___FALSEP(input_allow_special),
           !___FALSEP(input_echo),
           !___FALSEP(input_raw),
           !___FALSEP(output_raw),
           ___INT(speed));

  return e;
}
