is_separator_on_screen()
{
    if( ! m_layout_tree ) return false;

    const int separator_new = m_layout_tree->get_separator_new();
    if( ! separator_new ) return false;

    const RECTANGLE* rect = m_layout_tree->get_separator()->rect;
    if( ! rect ) return false;

    const int height_view = m_view.get_height();
    const int pos_y = get_vscr_val();
    if( rect->y + rect->height <= pos_y || rect->y > pos_y + height_view ) return false;

    return true;
}
