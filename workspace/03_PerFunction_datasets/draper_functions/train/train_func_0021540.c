err_handler(const char *msg) const THROWS(NCursesException)
{
  THROW(new NCursesException(msg));
}
