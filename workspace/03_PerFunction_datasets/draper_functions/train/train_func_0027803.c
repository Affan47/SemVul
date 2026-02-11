getList()
{

    QEventLoop eventLoop;
    QNetworkAccessManager networkMgr;

    connect(&networkMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(getListFinished(QNetworkReply*)));
    connect(&networkMgr, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    QByteArray out;


    QNetworkRequest request = QNetworkRequest(QUrl(ErgDBUrl + "api/list"));
    networkMgr.get(request);


    eventLoop.exec();
}
