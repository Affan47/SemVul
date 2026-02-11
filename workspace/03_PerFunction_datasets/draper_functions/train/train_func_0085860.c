gui_remove_deploy_unit( Unit *unit )
{
    List_Entry *entry;
    Unit *next_unit;
    entry = list_entry( left_deploy_units, unit );
    if ( entry->next->item )
        next_unit = entry->next->item;
    else
        if ( entry->prev->item )
            next_unit = entry->prev->item;
        else
            next_unit = 0;
    list_delete_item( left_deploy_units, unit );
    deploy_unit = next_unit;
    gui_add_deploy_units( gui->deploy_window->frame->contents );
    frame_apply( gui->deploy_window->frame );
}
