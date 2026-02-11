removeEmoticon(const QString &emo)
{
    QString emoticon = QFileInfo(emoticonsMap().key(emo.split(' '))).fileName();

    bool start = false;
    for (int i = 0; i < m_text.size(); ++i) {
        QString line = m_text.at(i);

        if (line.startsWith('#') || line.isEmpty()) {
            continue;
        }

        QRegExp re("^\\[(.*)\\]$");
        int pos = re.indexIn(line.trimmed());
        if (pos > -1) {
            if (!re.cap(1).compare("default", Qt::CaseInsensitive)) {
                start = true;
            } else {
                start = false;
            }
            continue;
        }

        if (!start) {
            continue;
        }

        QStringList splitted = line.split(' ');
        QString emoName;

        if (splitted.at(0) == "!") {
            emoName = splitted.at(1);
        } else {
            emoName = splitted.at(0);
        }

        if (emoName == emoticon) {
            m_text.removeAt(i);
            removeEmoticonIndex(emoticon, emo.split(' '));
            return true;
        }
    }

    return false;
}
