maybe_exit(int error)
{
  if (!first_error)
    first_error= error;
  if (ignore_errors)
    return;
  if (mysql)
    mysql_close(mysql);
  free_resources();
  exit(error);
}
