gui_render_module_info( const char *path, SDL_Surface *buffer )
{
    if ( path )
        group_set_active( gui->module_dlg->group, ID_MODULE_OK, 1 );
    else
        group_set_active( gui->module_dlg->group, ID_MODULE_OK, 0 );
}
