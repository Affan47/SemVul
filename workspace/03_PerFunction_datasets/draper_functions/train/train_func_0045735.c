folks_test_case_weak_method_test (gpointer fixture G_GNUC_UNUSED,
    gconstpointer test_data)
{
  const FolksTestCaseWeakMethod *wm = test_data;

  g_return_if_fail (wm->self != NULL);
  g_return_if_fail (FOLKS_IS_TEST_CASE (wm->self));

  wm->test (wm->self);
}
