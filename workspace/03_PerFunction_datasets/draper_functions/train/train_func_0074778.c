test_unicode_properties_nil (void)
{
  hb_unicode_funcs_t *uf = hb_unicode_funcs_create (NULL);

  g_assert (!hb_unicode_funcs_is_immutable (uf));
  _test_unicode_properties_nil (uf);

  hb_unicode_funcs_destroy (uf);
}
