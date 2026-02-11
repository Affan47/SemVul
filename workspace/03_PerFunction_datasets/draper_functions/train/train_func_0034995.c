test_enumerate_not_present (TestSlot      *test,
                            gconstpointer  unused)
{
  GPkcs11EnumerateState state;
  CK_ATTRIBUTE_TYPE types[] = { CKA_LABEL, CKA_ID };
  GError *error = NULL;
  GPkcs11Array *match;


  match = g_pkcs11_array_new ();


  state = g_pkcs11_slot_enumerate (test->not_present, NULL,
                                   match->attrs, match->count, FALSE,
                                   types, G_N_ELEMENTS (types),
                                   accumulate_check_not_called, NULL,
                                   NULL, &error);

  g_assert_cmpuint (state, ==, G_PKCS11_ENUMERATE_CONTINUE);
  g_assert_no_error (error);

  g_pkcs11_array_unref (match);
}
