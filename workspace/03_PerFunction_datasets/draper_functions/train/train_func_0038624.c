slot_preferences_image()
{
    if( m_path_selected.empty() ) return;
    std::string url = path2url( m_path_selected );

    SKELETON::PrefDiag* pref= CORE::PrefDiagFactory( get_parent_win(), CORE::PREFDIAG_IMAGE, url );
    pref->run();
    delete pref;
}
