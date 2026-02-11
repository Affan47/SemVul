is_values_list(const char *sql, char *nextc)
{
  if ((sql[0] == 'v' || sql[0] == 'V') &&
      (sql[1] == 'a' || sql[1] == 'A') &&
      (sql[2] == 'l' || sql[2] == 'L') &&
      (sql[3] == 'u' || sql[3] == 'U') &&
      (sql[4] == 'e' || sql[4] == 'E') &&
      (sql[5] == 's' || sql[5] == 'S'))
  {
    int i = 6;
    while (IS_SPACE(sql[i]))
      ++i;
    if (sql[i] == '(') {
      *nextc = ')';
      return i+1;
    }
  }
  return 0;
}
