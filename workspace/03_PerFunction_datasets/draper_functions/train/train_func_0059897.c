test_enumerate_fail_attributes (TestSlot     *test,
                                gconstpointer unused)
{
  GPkcs11EnumerateState state;
  GError *error = NULL;
  CK_ATTRIBUTE_TYPE types[] = { CKA_LABEL, CKA_ID };


  test->funcs.C_GetAttributeValue = mock_fail_C_GetAttributeValue;

  state = g_pkcs11_slot_enumerate (test->slot, NULL,
                                   NULL, 0, FALSE,
                                   types, G_N_ELEMENTS (types),
                                   accumulate_check_not_called, NULL,
                                   NULL, &error);

  g_assert_cmpuint (state, ==, G_PKCS11_ENUMERATE_FAILED);
  g_assert_error (error, G_PKCS11_ERROR, CKR_FUNCTION_FAILED);
  g_error_free (error);
}
