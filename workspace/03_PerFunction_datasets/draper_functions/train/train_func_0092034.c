saveXmlUrlFileLinks()
{
    if (!d->_useUidAsFileName)
        return false;
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    Q_EMIT progressMessageChanged(tr("Saving cache"));
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    QDomDocument doc("FreeMedForms");
    QDomElement element = doc.createElement(::TAG_ROOT);
    doc.appendChild(element);
    QDir output(outputPath());
    int count = d->_downloadedUrl.count();
    int i = 0;


    foreach(const DownloadedUrl &url, d->_downloadedUrl) {
        QDomElement urlElement = doc.createElement(::TAG_URLROOT);
        urlElement.setAttribute(::ATTRIB_URL, url.url.toString());
        urlElement.setAttribute(::ATTRIB_FILENAME, output.relativeFilePath(url.outputFile));
        urlElement.setAttribute(::ATTRIB_ERRORMSG, url.errorMessage);
        urlElement.setAttribute(::ATTRIB_ERROR, url.networkError);
        ++i;
        if (i % 10 == 0) {
            int permille = i/count*1000;
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
            Q_EMIT downloadProgressPermille(permille);
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        element.appendChild(urlElement);
    }
    bool ok = Utils::saveStringToFile(QString("<?xml version='1.0' encoding='UTF-8'?>\n" + doc.toString(2)),
                                   QString("%1/%2").arg(outputPath()).arg(::DEFAULT_XML_FILENAME),
                                   Utils::Overwrite, Utils::DontWarnUser);
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    Q_EMIT progressMessageChanged(tr("Cache saved"));
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    return ok;
}
