skipMoves()
{
    QString tag = m_index.tagValue(TagNamePlyCount, m_count - 1);
    if(tag == "?")
    {
        tag.clear();
    }
    if(!tag.isEmpty())
    {
        while(!onlyWhite(m_lineBuffer) && !m_file->atEnd())
        {
            skipLine();
        }

        tag = QString::number((tag.toInt() + 1) / 2);
        m_index.setTag("Length", tag, m_count - 1);
    }
    else
    {
        QRegExp gameNumber("\\s(\\d+)\\s*\\.");

        QString gameText = " ";

        while(!onlyWhite(m_lineBuffer) && !m_file->atEnd())
        {
            gameText += QString(m_lineBuffer) + " ";
            skipLine();
        }

        gameText = gameText.remove(QRegExp("\\([^\\(\\)]*\\)"));

        gameNumber.lastIndexIn(gameText);
        m_index.setTag("Length", gameNumber.cap(1), m_count - 1);
    }


    while(onlyWhite(m_lineBuffer) && !m_file->atEnd())
    {
        skipLine();
    }

    if(m_utf8)
    {
        QTextStream textStream(m_lineBuffer);
        m_currentLine = textStream.readLine().simplified();
    }
    else
    {
        QTextStream textStream(m_lineBuffer);
        QTextCodec* textCodec = QTextCodec::codecForName("ISO 8859-1");
        if(textCodec)
        {
            textStream.setCodec(textCodec);
        }
        m_currentLine = textStream.readLine().simplified();
    }
}
