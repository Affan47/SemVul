addEmoticon(const QString &emo, const QString &text, AddEmoticonOption option)
{
    KEmoticonsProvider::addEmoticon(emo, text, option);

    const QStringList splitted = text.split(' ');
    QDomElement fce = m_themeXml.firstChildElement("icondef");

    if (fce.isNull()) {
        return false;
    }

    QDomElement emoticon = m_themeXml.createElement("icon");
    fce.appendChild(emoticon);
    QStringList::const_iterator constIterator;

    for (constIterator = splitted.begin(); constIterator != splitted.end(); ++constIterator) {
        QDomElement emotext = m_themeXml.createElement("text");
        QDomText txt = m_themeXml.createTextNode((*constIterator).trimmed());
        emotext.appendChild(txt);
        emoticon.appendChild(emotext);
    }

    QDomElement emoElement = m_themeXml.createElement("object");
    KMimeType::Ptr mimePtr = KMimeType::findByPath(emo, 0, true);
    emoElement.setAttribute("mime", mimePtr->name());
    QDomText txt = m_themeXml.createTextNode(QFileInfo(emo).fileName());

    emoElement.appendChild(txt);
    emoticon.appendChild(emoElement);

    addEmoticonIndex(emo, splitted);
    addEmoticonsMap(emo, splitted);
    return true;
}
