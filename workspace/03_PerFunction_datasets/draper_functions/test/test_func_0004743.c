addEmoticon(const QString &emo, const QString &text, AddEmoticonOption option)
{
    KEmoticonsProvider::addEmoticon(emo, text, option);

    const QStringList splitted = text.split(' ');
    QDomElement fce = m_themeXml.firstChildElement("plist").firstChildElement("dict").firstChildElement("dict");

    if (fce.isNull()) {
        return false;
    }

    QDomElement emoticon = m_themeXml.createElement("key");
    emoticon.appendChild(m_themeXml.createTextNode(QFileInfo(emo).fileName()));
    fce.appendChild(emoticon);

    QDomElement dict = m_themeXml.createElement("dict");
    QDomElement el = m_themeXml.createElement("key");
    el.appendChild(m_themeXml.createTextNode("Equivalents"));
    dict.appendChild(el);

    QDomElement arr = m_themeXml.createElement("array");

    QStringList::const_iterator constIterator;
    for (constIterator = splitted.begin(); constIterator != splitted.end(); ++constIterator) {
        QDomElement emoText = m_themeXml.createElement("string");
        QDomText txt = m_themeXml.createTextNode((*constIterator).trimmed());
        emoText.appendChild(txt);
        arr.appendChild(emoText);
    }

    dict.appendChild(arr);

    el = m_themeXml.createElement("key");
    el.appendChild(m_themeXml.createTextNode("Name"));
    dict.appendChild(el);

    el = m_themeXml.createElement("string");
    el.appendChild(m_themeXml.createTextNode(QFileInfo(emo).baseName()));
    dict.appendChild(el);

    fce.appendChild(dict);

    addEmoticonIndex(emo, splitted);
    addEmoticonsMap(emo, splitted);
    return true;
}
