GetBrowse_MarksFromHash( EditorBase* eb)

{


    EbBrowse_MarksHash::iterator it = m_EbBrowse_MarksHash.find(eb);
    if ( it == m_EbBrowse_MarksHash.end() ) return 0;
    return it->second;
}
