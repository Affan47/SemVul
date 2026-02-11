urlChanged(const QUrl &url)
{
    if (url.toString().startsWith("http://www.goldencheetah.org/?state=&code=") ||
        url.toString().startsWith("http://www.goldencheetah.org/?code=")) {
        QString code = url.toString().right(url.toString().length()-url.toString().indexOf("code=")-5);

        QByteArray data;
        QUrl params;
        QString urlstr = "";

        if (site == STRAVA) {
            urlstr = QString("https://www.strava.com/oauth/token?");
            params.addQueryItem("client_id", GC_STRAVA_CLIENT_ID);
#ifdef GC_STRAVA_CLIENT_SECRET
            params.addQueryItem("client_secret", GC_STRAVA_CLIENT_SECRET);
#endif
            params.addQueryItem("redirect_uri", "http://www.goldencheetah.org/");
        }
        else if (site == TWITTER) {
            urlstr = QString("http://api.twitter.com/oauth/token?");

        }
        else if (site == CYCLING_ANALYTICS) {
            urlstr = QString("https://www.cyclinganalytics.com/api/token?");
            params.addQueryItem("client_id", GC_CYCLINGANALYTICS_CLIENT_ID);
#ifdef GC_CYCLINGANALYTICS_CLIENT_SECRET
            params.addQueryItem("client_secret", GC_CYCLINGANALYTICS_CLIENT_SECRET);
#endif
            params.addQueryItem("grant_type", "authorization_code");
        }
        params.addQueryItem("code", code);

        data = params.encodedQuery();

        QUrl url = QUrl( urlstr);
        QNetworkRequest request = QNetworkRequest(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

        requestToken = true;
        view->load(request,QNetworkAccessManager::PostOperation,data);
    }
}
