checkAuth(const cxxtools::http::Request& request) const
{
  cxxtools::http::Request::Auth auth = request.auth();

  if (auth.user != "cxxtools" || auth.password != "mypassword")
    return false;

  return true;
}
