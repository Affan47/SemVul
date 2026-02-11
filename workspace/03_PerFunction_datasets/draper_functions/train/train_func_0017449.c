GWidgetGetCurrentFocusWindow(void) {
    GTopLevelD *td;
    if ( current_focus_window==NULL )
return( NULL );
    td = (GTopLevelD *) (current_focus_window->widget_data);
    if ( td->gfocus!=NULL )
return( td->gfocus->base );
return( td->wfocus );
}
