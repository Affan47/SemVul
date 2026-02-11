skipJunk()
{
    IndexBaseType fp = -2;
    if(m_file->atEnd())
    {
        fp = -1;
    }

    while((!m_lineBuffer.length()
            || (m_lineBuffer[0] != '[' && m_lineBuffer[0] != '1'))
            && !m_file->atEnd())
    {
        fp = m_file->pos();
        skipLine();
    }

    if(fp == -2)
    {
        fp = m_file->pos() - m_lineBuffer.size();
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

    if(m_inComment || !m_currentLine.startsWith("["))
    {
        m_currentLine.replace("(", " ( ");
        m_currentLine.replace(")", " ) ");
        m_currentLine.replace("{", " { ");
        m_currentLine.replace("}", " } ");
        m_currentLine.replace("$", " $");
    }

    return fp;
}
