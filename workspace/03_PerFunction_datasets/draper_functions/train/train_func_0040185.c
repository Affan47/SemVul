reset (void)
{
  if (unlikely (hb_object_is_inert (this)))
    return;

  hb_unicode_funcs_destroy (unicode);
  unicode = hb_unicode_funcs_get_default ();

  clear ();
}
