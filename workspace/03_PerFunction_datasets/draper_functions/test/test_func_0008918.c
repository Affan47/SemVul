gui_radiogroup_is_checked( GuiWidget *widget, int id )
{
    if ( widget->type != GUI_RADIOGROUP )
        return 0;
    if ( id >= widget->spec.radiogroup.size || id < 0 )
        return 0;
    return widget->spec.radiogroup.checks[id];
}
