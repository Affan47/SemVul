addActionsFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return;

    QString currentUserAgentString = WebPage::userAgent();
    QXmlStreamReader xml(&file);
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == QLatin1String("separator")) {
            addSeparator();
            continue;
        }
        if (xml.isStartElement() && xml.name() == QLatin1String("useragent")) {
            QXmlStreamAttributes attributes = xml.attributes();
            QString title = attributes.value(QLatin1String("description")).toString();
            QString userAgent = attributes.value(QLatin1String("useragent")).toString();

            QAction *action = new QAction(this);
            action->setText(title);
            action->setData(userAgent);
            action->setToolTip(userAgent);
            action->setCheckable(true);
            action->setChecked(userAgent == currentUserAgentString);
            connect(action, SIGNAL(triggered()), this, SLOT(changeUserAgent()));
            addAction(action);
        }
    }
    if (xml.hasError()) {
        qDebug() << "Error reading custom user agents" << xml.errorString();

    }
}
