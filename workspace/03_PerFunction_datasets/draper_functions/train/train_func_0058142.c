set(const config& conf)
{
  timeout = conf.get_int("timeout", 600);
  listen_backlog = conf.get_int("listen_backlog", 256);
  std::string node = conf.get_str("host", "");
  std::string port = conf.get_str("port", "");
  if (!node.empty() || !port.empty()) {
    if (family == AF_UNIX || node == "/") {
      set_unix_domain(port.c_str());
    } else {
      const char *nd = node.empty() ? 0 : node.c_str();
      if (resolve(nd, port.c_str()) != 0) {
	fatal_exit("getaddrinfo failed: " + node + ":" + port);
      }
    }
  }
  sndbuf = conf.get_int("sndbuf", 0);
  rcvbuf = conf.get_int("rcvbuf", 0);
}
