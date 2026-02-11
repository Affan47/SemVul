get_nondigit_option (int argc, char *const *argv, intmax_t *default_context)
{
  static int prev_digit_optind = -1;
  int this_digit_optind, was_digit;
  char buf[INT_BUFSIZE_BOUND (intmax_t) + 4];
  char *p = buf;
  int opt;

  was_digit = 0;
  this_digit_optind = optind;
  while (1)
    {
      opt = getopt_long (argc, (char **) argv, short_options,
                         long_options, NULL);
      if ( ! ('0' <= opt && opt <= '9'))
        break;

      if (prev_digit_optind != this_digit_optind || !was_digit)
        {

          p = buf;
        }
      else
        {


          p -= buf[0] == '0';
        }

      if (p == buf + sizeof buf - 4)
        {


          strcpy (p, "...");
          p += 3;
          break;
        }
      *p++ = opt;

      was_digit = 1;
      prev_digit_optind = this_digit_optind;
      this_digit_optind = optind;
    }
  if (p != buf)
    {
      *p = '\0';
      context_length_arg (buf, default_context);
    }

  return opt;
}
