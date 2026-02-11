keysym_to_string (KeySym keysym, unsigned int modifier)
{
  static char *null_string = "NULL";
  struct sbuf *name;
  char *tmp;

  name = sbuf_new (0);

  if (modifier & RP_SHIFT_MASK) sbuf_concat (name, "S-");
  if (modifier & RP_CONTROL_MASK) sbuf_concat (name, "C-");
  if (modifier & RP_META_MASK) sbuf_concat (name, "M-");
  if (modifier & RP_ALT_MASK) sbuf_concat (name, "A-");
  if (modifier & RP_HYPER_MASK) sbuf_concat (name, "H-");
  if (modifier & RP_SUPER_MASK) sbuf_concat (name, "s-");


  tmp = XKeysymToString (keysym);
  if (tmp == NULL)
    tmp = null_string;

  sbuf_concat (name, tmp);


  tmp = sbuf_get (name);
  free (name);

  return tmp;
}
