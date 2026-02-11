addFromFile(const QString & txtFilePath)
{
    QFile file(txtFilePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;


    QRegExp splitNonWords("\\W");
    QTextStream ts(&file);
    while (!ts.atEnd()) {
        QStringList words = ts.readLine().split(splitNonWords, QString::SkipEmptyParts);
        foreach (const QString & word, words)
            addWord(word);
    }
    return true;
}
