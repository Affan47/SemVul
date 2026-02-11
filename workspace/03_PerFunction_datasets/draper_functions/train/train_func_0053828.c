__register_printf_modifier (const wchar_t *str)
{
  if (str[0] == L'\0')
    {
    einval:
      __set_errno (EINVAL);
      return -1;
    }

  const wchar_t *wc = str;
  while (*wc != L'\0')
    if (*wc < 0 || *wc > (wchar_t) UCHAR_MAX)
      goto einval;
    else
      ++wc;

  if (next_bit / 8 == sizeof (((struct printf_info *) NULL)->user))
    {
      __set_errno (ENOSPC);
      return -1;
    }

  int result = -1;
  __libc_lock_lock (lock);

  if (__printf_modifier_table == NULL)
    {
      __printf_modifier_table = calloc (UCHAR_MAX,
					sizeof (*__printf_modifier_table));
      if (__printf_modifier_table == NULL)
	goto out;
    }


  struct printf_modifier_record *newp = malloc (sizeof (*newp)
						+ ((wc - str)
						   * sizeof (wchar_t)));
  if (newp == NULL)
    goto out;

  newp->next = __printf_modifier_table[(unsigned char) *str];
  newp->bit = 1 << next_bit++;
  __wmemcpy (newp->str, str + 1, wc - str);

  __printf_modifier_table[(unsigned char) *str] = newp;

  result = newp->bit;

 out:
  __libc_lock_unlock (lock);

  return result;
}
