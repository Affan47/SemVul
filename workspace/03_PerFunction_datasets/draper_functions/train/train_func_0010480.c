create_layout_header()
{
    m_last_layout = NULL;
    m_id_layout = 0;
    m_id_header += STEP_ID;

    int classid = CORE::get_css_manager()->get_classid( "res" );
    LAYOUT* header = create_layout_div( classid );
    header->type = DBTREE::NODE_HEADER;
    m_last_layout = header;

    if( m_last_header ) m_last_header->next_header = header;
    m_last_header = header;
    header->header = header;

    return header;
}
