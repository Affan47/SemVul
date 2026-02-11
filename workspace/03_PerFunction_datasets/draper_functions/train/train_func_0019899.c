getFoldersParameters(QString path)
{
    QString xmlDoctype = QString(XML_DOCTYPE);
    QString xmlOpening = QString(XML_OPENING);
    QString xmlClosing = QString(XML_CLOSING);
    QString xmlEnding = QString(XML_ENDING);
    QString xmlPathElement = QString(PATH);
    QString xmlParametersDocument = QString(xmlDoctype + XML_FOLDERS + xmlEnding);
    QString xmlKontrolPackElement = QString(KONTROLPACK);
    QString xmlHostnameElement = QString(HOSTNAME);
    QString xmlSystemElement = QString(SYSTEM);
    QString drive = QString(DRIVE);
    QString drives = QString(DRIVES);

    QFileInfoList drivesInfo = QDir::drives();

    QString xmlDocument = QString("");

    xmlDocument.append(xmlParametersDocument);
    xmlDocument.append(xmlOpening + xmlKontrolPackElement + xmlEnding);
    xmlDocument.append(xmlOpening + xmlHostnameElement + xmlEnding);
    xmlDocument.append(QHostInfo::localHostName());
    xmlDocument.append(xmlClosing + xmlHostnameElement + xmlEnding);

    xmlDocument.append(xmlOpening + xmlSystemElement + xmlEnding);
#ifdef WIN32
    xmlDocument.append(WINDOWS);
#elif defined (linux)
    xmlDocument.append(LINUX);
#elif defined __APPLE__
    xmlDocument.append(MACOSX);
#elif defined (__FreeBSD__)
    xmlDocument.append(FREEBSD);
#else
    xmlDocument.append(LINUX);
#endif
    xmlDocument.append(xmlClosing + xmlSystemElement + xmlEnding);

    xmlDocument.append(xmlOpening + xmlPathElement + xmlEnding);
    xmlDocument.append(path);
    xmlDocument.append(xmlClosing + xmlPathElement + xmlEnding);

    appendFolderAndFileInfo(xmlDocument, path);

    xmlDocument.append( xmlOpening + drives + xmlEnding );
    for( int k = 0; k < drivesInfo.size(); k++ )
    {
        xmlDocument.append( xmlOpening + drive + xmlEnding );
        QFileInfo driveName = drivesInfo.at(k);
        xmlDocument.append(driveName.filePath());
        xmlDocument.append( xmlClosing + drive + xmlEnding );
    }
    xmlDocument.append( xmlClosing + drives + xmlEnding );


    xmlDocument.append(xmlClosing + xmlKontrolPackElement + xmlEnding);

    return xmlDocument;
}
