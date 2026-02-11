square_as_move_to_string_test (void)
{

  g_assert_cmpstr("--", ==, square_as_move_to_string(pass_move));
  g_assert_cmpstr("D5", ==, square_as_move_to_string(D5));

}
