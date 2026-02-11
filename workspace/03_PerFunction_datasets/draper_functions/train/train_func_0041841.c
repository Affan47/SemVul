BackForwardButton( const std::string& url, const bool back )
    : SKELETON::MenuButton( true, ( back ? ICON::BACK : ICON::FORWARD ) ),
      m_url( url ),
      m_back( back )
{}
