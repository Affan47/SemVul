gui_spinbutton_set_value( GuiWidget *widget, int value )
{
    char aux[GUI_SPINBUTTON_LENGTH + 1];
    if ( widget->type == GUI_SPINBUTTON ) {
        widget->spec.spinbutton.value = value;
        snprintf( aux, GUI_SPINBUTTON_LENGTH + 1, "%i", value );
        gui_edit_set_text( widget->spec.spinbutton.edit, aux );
    }
}
