read_rtx_variadic (struct map_value **mode_maps, rtx form)
{
  char c = '(';
  rtx p = form, q;

  do
    {
      unread_char (c);

      q = rtx_alloc (GET_CODE (p));
      PUT_MODE (q, GET_MODE (p));

      XEXP (q, 0) = XEXP (p, 1);
      XEXP (q, 1) = read_nested_rtx (mode_maps);

      XEXP (p, 1) = q;
      p = q;
      c = read_skip_spaces ();
    }
  while (c == '(');
  unread_char (c);
  return form;
}
