test_toggle()
{
  SUITE_START("toggle");

  BIT_ARRAY* arr = bit_array_create(0);
  _test_toggle_region(arr, 0, 0);

  bit_array_resize(arr, 10);
  bit_array_set_bits(arr, 4, 2,3,6,9);
  _test_toggle_region(arr, 3, 6);
  _test_toggle_region(arr, 0, 10);

  bit_array_resize(arr, 80);
  bit_array_set_bits(arr, 8, 0,20,50,62,64,70,75,79);
  _test_toggle_region(arr, 25, 50);

  bit_array_resize(arr, 100);
  bit_array_clear_all(arr);
  _test_toggle_region(arr, 0, 100);
  _test_toggle_region(arr, 0, 0);
  _test_toggle_region(arr, 1, 1);
  _test_toggle_region(arr, 3, 1);
  _test_toggle_region(arr, 20, 80);
  _test_toggle_region(arr, 0, 64);
  _test_toggle_region(arr, 64, 36);

  int i;
  for(i = 0; i < 1000; i += 50)
  {
    bit_array_resize(arr, i);
    bit_array_random(arr, 0.5f);
    _test_toggle_region(arr, i / 2, i - i / 2);
  }

  bit_array_free(arr);

  SUITE_END();
}
