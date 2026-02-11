initialize()
{
    if(m_outputType == Pgn)
    {
        m_newlineChar = "\n";
    }
    else if(m_outputType == Html)
    {
        m_newlineChar = "<br>\n";
    }
    else if(m_outputType == Latex)
    {
        m_newlineChar = "\n";
    }
    else if(m_outputType == NotationWidget)
    {
        m_newlineChar = "<br>\n";
    }
    readTemplateFile(m_templateFilename);
}
