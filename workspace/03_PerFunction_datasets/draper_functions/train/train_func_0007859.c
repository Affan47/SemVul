free_up (fixture_t *fixture)
{
  g_assert_cmpint (fixture->freed, ==, 0);
  fixture->freed++;
}
