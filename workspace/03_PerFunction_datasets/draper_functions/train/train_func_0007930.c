EditTreeView( const std::string& url, const std::string& dndtarget, EditColumns& columns,
                            const bool use_usr_fontcolor, const std::string& fontname, const int colorid_text, const int colorid_bg, const int colorid_bg_even )
    : DragTreeView( url, dndtarget, use_usr_fontcolor, fontname, colorid_text, colorid_bg, colorid_bg_even ),
      m_url( url ),
      m_columns( columns )
{
    setup();
}
