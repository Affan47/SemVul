StartElement(const char * name, const char **atts)
    {
    RestXMLParser::StartElement(name,atts);
    if(!m_CurrentTag.compare("/rsp/bitstreams/data"))
      {
      m_Bitstream = new mdo::Bitstream;
      }
    m_CurrentValue = "";
    }
