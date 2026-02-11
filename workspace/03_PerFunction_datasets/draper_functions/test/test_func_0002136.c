download()
{
    QString url = appsettings->cvalue(main->cyclist, GC_DVURL, "").toString();
    if (url == "") return false;

    QNetworkRequest request = QNetworkRequest(QUrl(url));

    QByteArray *queryText = new QByteArray( "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
                                            "<C:calendar-query xmlns:D=\"DAV:\""
                                            "                 xmlns:C=\"urn:ietf:params:xml:ns:caldav\">"
                                            " <D:prop>"
                                            "   <D:getetag/>"
                                            "   <C:calendar-data/>"
                                            " </D:prop>"
                                            " <C:filter>"
                                            "   <C:comp-filter name=\"VCALENDAR\">"
                                            "     <C:comp-filter name=\"VEVENT\">"
                                            "       <C:time-range end=\"20200101T000000Z\" start=\"20000101T000000Z\"/>"
                                            "     </C:comp-filter>"
                                            "   </C:comp-filter>"
                                            " </C:filter>"
                                            "</C:calendar-query>\r\n");

    request.setRawHeader("Depth", "0");
    request.setRawHeader("Content-Type", "application/xml; charset=\"utf-8\"");
    request.setRawHeader("Content-Length", (QString("%1").arg(queryText->size())).toLatin1());

    QBuffer *query = new QBuffer(queryText);

    mode = Events;
    QNetworkReply *reply = nam->sendCustomRequest(request, "REPORT", query);
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(main, tr("CalDAV REPORT url error"), reply->errorString());
        mode = None;
        return false;
    }
    return true;
}
