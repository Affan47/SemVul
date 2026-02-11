test_add_find (TestArray      *test,
               gconstpointer   data)
{
  CK_ATTRIBUTE attr;
  const CK_ATTRIBUTE *check;
  const gchar *value = "test";

  attr.type = CKA_LABEL;
  attr.ulValueLen = strlen (value) + 1;
  attr.pValue = (gpointer)value;
  g_pkcs11_array_add (test->array, &attr);
  memset (&attr, 0, sizeof (attr));

  check = g_pkcs11_array_find (test->array, CKA_LABEL);
  g_assert (check != NULL);
  g_assert_cmpuint ((guint)check->ulValueLen, ==, strlen (value) + 1);
  g_assert_cmpstr (check->pValue, ==, value);
  g_assert (check->pValue != value);


  g_assert (check != &attr);

  check = g_pkcs11_array_find (test->array, CKA_ID);
  g_assert (check == NULL);
  g_assert_cmpuint (test->array->count, ==, 1);


  attr.type = CKA_LABEL;
  attr.ulValueLen = 3;
  attr.pValue = "bye";
  g_pkcs11_array_add (test->array, &attr);
  g_assert_cmpuint (test->array->count, ==, 2);
}
