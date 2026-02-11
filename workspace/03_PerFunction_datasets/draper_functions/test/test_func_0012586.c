check_handle (SANE_Handle handle)
{
  Test_Device *test_device = first_test_device;

  while (test_device)
    {
      if (test_device == (Test_Device *) handle)
	return SANE_TRUE;
      test_device = test_device->next;
    }
  return SANE_FALSE;
}
