setContentType(const std::string &value)
{
    if (value.empty())
      setHeaderValue("Content-type", "text/html");
    else
      setHeaderValue("Content-type", value);
}
