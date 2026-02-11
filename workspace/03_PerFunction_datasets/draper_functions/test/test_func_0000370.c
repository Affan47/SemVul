loadTheme(const QString &path)
{
    KEmoticonsProvider::loadTheme(path);

    QFile fp(path);

    if (!fp.exists()) {
        kWarning() << path << "doesn't exist!";
        return false;
    }

    if (!fp.open(QIODevice::ReadOnly)) {
        kWarning() << fp.fileName() << "can't open ReadOnly!";
        return false;
    }

    QString error;
    int eli, eco;
    if (!m_themeXml.setContent(&fp, &error, &eli, &eco)) {
        kWarning() << fp.fileName() << "can't copy to xml!";
        kWarning() << error << "line:" << eli << "column:" << eco;
        fp.close();
        return false;
    }

    fp.close();

    QDomElement fce = m_themeXml.firstChildElement("messaging-emoticon-map");

    if (fce.isNull())
        return false;

    QDomNodeList nl = fce.childNodes();

    clearEmoticonsMap();

    for (uint i = 0; i < nl.length(); i++) {
        QDomElement de = nl.item(i).toElement();

        if (!de.isNull() && de.tagName() == "emoticon") {
            QDomNodeList snl = de.childNodes();
            QStringList sl;

            for (uint k = 0; k < snl.length(); k++) {
                QDomElement sde = snl.item(k).toElement();

                if (!sde.isNull() && sde.tagName() == "string") {
                    sl << sde.text();
                }
            }

            QString emo = KGlobal::dirs()->findResource("emoticons", themeName() + '/' + de.attribute("file"));

            if (emo.isEmpty()) {
                QList<QByteArray> ext = QImageReader::supportedImageFormats();

                for (int j = 0; j < ext.size(); ++j) {
                    emo = KGlobal::dirs()->findResource("emoticons", themeName() + '/' + de.attribute("file") + '.' + ext.at(j));
                    if (!emo.isEmpty()) {
                        break;
                    }
                }

                if (emo.isEmpty()) {
                    continue;
                }
            }

            addEmoticonIndex(emo, sl);
            addEmoticonsMap(emo, sl);
        }
    }

    return true;
}
