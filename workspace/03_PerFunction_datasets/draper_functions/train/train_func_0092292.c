fromDomElement(const QDomElement& element, const QStringList& searchPath)
{
    if( element.isNull() )
        return;

    QString file = element.attribute("file");
    if( ! file.isEmpty() ) {
        if( QFileInfo(file).exists() ) {
            setFile(file);
        }
        else {
            foreach (const QString& packagepath, searchPath) {
                QFileInfo fi(QDir(packagepath), file);
                if( fi.exists() ) {
                    setFile( fi.absoluteFilePath() );
                    break;
                }
            }
        }
    }

    d->version = QVariant( element.attribute("version",QString(d->version)) ).toInt();

    setText( i18n( element.attribute("text").toUtf8() ) );
    setDescription( i18n( element.attribute("comment").toUtf8() ) );
    setEnabled( true );
    setInterpreter( element.attribute("interpreter") );
    setEnabled( QVariant(element.attribute("enabled","true")).toBool() && isEnabled() );

    QString icon = element.attribute("icon");
    if( icon.isEmpty() && ! d->scriptfile.isNull() )
        icon = KMimeType::iconNameForUrl( KUrl(d->scriptfile) );
    setIconName( icon );

    const QString code = element.attribute("code");
    if( ! code.isNull() )
        setCode(code.toUtf8());

    for(QDomNode node = element.firstChild(); ! node.isNull(); node = node.nextSibling()) {
        QDomElement e = node.toElement();
        if( ! e.isNull() ) {
            if( e.tagName() == "property" ) {
                const QString n = e.attribute("name", QString());
                if( ! n.isNull() ) {
                    #ifdef KROSS_ACTION_DEBUG
                        krossdebug(QString("Action::readDomElement: Setting property name=%1 value=%2").arg(n).arg(e.text()));
                    #endif
                    setProperty(n.toLatin1().constData(), QVariant(e.text()));
                }
            }
        }
    }
}
