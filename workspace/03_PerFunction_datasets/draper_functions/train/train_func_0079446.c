updateProxySettings()
{
	QSettings settings;
	QNetworkProxy proxy;

	int proxyMode = settings.value("network/proxyMode", ActionTools::Settings::PROXY_SYSTEM).toInt();
	switch(proxyMode)
	{
	case ActionTools::Settings::PROXY_NONE:
		proxy.setType(QNetworkProxy::NoProxy);
		break;
	case ActionTools::Settings::PROXY_SYSTEM:
		{
			QUrl url(Global::CONNECTIVITY_URL);
			QNetworkProxyQuery networkProxyQuery(url);
			QList<QNetworkProxy> listOfProxies = QNetworkProxyFactory::systemProxyForQuery(networkProxyQuery);
			if(!listOfProxies.isEmpty())
				proxy = listOfProxies.first();
			else
				proxy.setType(QNetworkProxy::NoProxy);
		}
		break;
	case ActionTools::Settings::PROXY_CUSTOM:
		{
			int type = settings.value("network/proxyType", ActionTools::Settings::PROXY_TYPE_HTTP).toInt();
			QNetworkProxy proxy;

			if(type == ActionTools::Settings::PROXY_TYPE_HTTP)
				proxy.setType(QNetworkProxy::HttpProxy);
			else
				proxy.setType(QNetworkProxy::Socks5Proxy);

			proxy.setHostName(settings.value("network/proxyHost", QString("0.0.0.0")).toString());
			proxy.setPort(settings.value("network/proxyPort", 0).toInt());
			proxy.setUser(settings.value("network/proxyUser", QString()).toString());
			proxy.setPassword(settings.value("network/proxyPassword", QString()).toString());
		}
		break;
	}

	QNetworkProxy::setApplicationProxy(proxy);
}
