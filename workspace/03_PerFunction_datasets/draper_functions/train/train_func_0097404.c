_nl_get_walt_digit (unsigned int number, struct __locale_data *current)
{
  const wchar_t *result = NULL;
  struct lc_time_data *data;

  if (number >= 100 || CURRENT_WSTR (_NL_WALT_DIGITS)[0] == L'\0')
    return NULL;

  __libc_rwlock_wrlock (__libc_setlocale_lock);

  if (current->private.time == NULL)
    {
      current->private.time = malloc (sizeof *current->private.time);
      if (current->private.time == NULL)
	goto out;
      memset (current->private.time, 0, sizeof *current->private.time);
      current->private.cleanup = &_nl_cleanup_time;
    }
  data = current->private.time;

  if (! data->walt_digits_initialized)
    {
      const wchar_t *ptr = CURRENT_WSTR (_NL_WALT_DIGITS);
      size_t cnt;

      data->walt_digits_initialized = 1;

      if (ptr != NULL)
	{
	  data->walt_digits = malloc (100 * sizeof (const uint32_t *));
	  if (data->walt_digits != NULL)
	    for (cnt = 0; cnt < 100; ++cnt)
	      {
		data->walt_digits[cnt] = ptr;


		ptr = wcschr (ptr, L'\0') + 1;
	      }
	}
    }

  if (data->walt_digits != NULL)
    result = data->walt_digits[number];

 out:
  __libc_rwlock_unlock (__libc_setlocale_lock);

  return (wchar_t *) result;
}
