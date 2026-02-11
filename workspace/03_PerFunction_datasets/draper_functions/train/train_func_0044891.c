onLayoutUpdate(uint32_t layout, void * obj)
{
    dbg(" EVENT LAYOUT CHANGED %u", layout);
    char * layout_name = NULL;
    int result =  kbdd_get_layout_name(layout, &layout_name);
    if ( ! result ) layout_name = NULL;
    dbg(" Keyboard layout %s", layout_name);
    m_kbdd_service_update_layout((MKbddService *)obj, layout, layout_name);
    if (layout_name)
      free(layout_name);
}
