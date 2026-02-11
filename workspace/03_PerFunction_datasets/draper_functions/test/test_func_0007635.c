GWindowGetCurrentFocusGadget(void) {
    GTopLevelD *td;
    if ( current_focus_window==NULL )
return( NULL );
    td = (GTopLevelD *) (current_focus_window->widget_data);
return( td->gfocus );
}
