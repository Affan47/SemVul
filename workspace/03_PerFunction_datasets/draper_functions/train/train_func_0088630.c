createMessageRawContent(const QString &plainTextMessage)
{
    HprimRawContent *content = new HprimRawContent;
    QString corrected = plainTextMessage;


    if (corrected.contains(::EOF_TAG1, Qt::CaseInsensitive)
            || corrected.contains(::EOF_TAG2, Qt::CaseInsensitive)) {
        corrected = corrected.remove(::EOF_TAG1, Qt::CaseInsensitive);
        corrected = corrected.remove(::EOF_TAG2, Qt::CaseInsensitive);
    }


    if (corrected.contains("\r")) {
        corrected = corrected.replace("\r", "<#@cr@#>");
        corrected = corrected.replace("<#@cr@#>\n", "\n");
        corrected = corrected.replace("<#@cr@#>", "\n");
    }


    if (!corrected.endsWith("\n"))
        corrected.append("\n");
    content->setRawSource(QString("%1%2\n%3\n")
                          .arg(corrected)
                          .arg(::EOF_TAG1)
                          .arg(::EOF_TAG2));
    return *content;
}

}
