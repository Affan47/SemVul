dumpWords() const
{
    QString dumpString;
    bool first = true;
    foreach (const Word & word, m_words) {
        if (first)
            first = false;
        else
            dumpString += ", ";
        dumpString += QString("\"%1\"").arg(word.lowerString);
    }
    qWarning("WordList: %s", qPrintable(dumpString));
}
