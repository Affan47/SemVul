Url(const String &u)
{
    HtConfiguration* config= HtConfiguration::config();
    if (url)
      delete url;
    url = new URL(u);


    if (proxy)
    	delete proxy;
    proxy = 0;


    const String proxyURL = config->Find(url,"http_proxy");


    if (proxyURL.length())
    {
        proxy = new URL(proxyURL);
        proxy->normalize();

        setProxyUsernamePassword(config->Find(url,"http_proxy_authorization"));
    }


    setUsernamePassword(config->Find(url,"authorization"));

}
