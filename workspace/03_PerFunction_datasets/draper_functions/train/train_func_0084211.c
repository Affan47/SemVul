parseAndStore
(const std::string& setCookieString,
 const std::string& requestHost,
 const std::string& defaultPath,
 time_t now)
{
  auto cookie = cookie::parse(setCookieString, requestHost, defaultPath, now);
  return cookie && store(std::move(cookie), now);
}
