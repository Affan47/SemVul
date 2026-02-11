getfqdn(void) {
    std::string name;
    char hostname[256];
    char domainname[256];

    if ((!gethostname(hostname, 255)) && (!getdomainname(domainname, 255))) {
      name.append(hostname);
      if(strcmp(domainname, "(none)")) {
        if (*domainname == '.')
          name.append(domainname);
        else {
          name.append(".").append(domainname);
        }
      }
    }
    return name;
  }
