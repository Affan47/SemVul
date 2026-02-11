fl_deactivate_form( FL_FORM * form )
{
    if ( ! form )
    {
        M_err( "fl_deactivate_form", "NULL form" );
        return;
    }

    if (    ! form->deactivated
         && fli_int.mouseobj
         && fli_int.mouseobj->form == form )
        fli_handle_object( fli_int.mouseobj, FL_LEAVE, 0, 0, 0, NULL, 1 );

    if ( ! form->deactivated && form->deactivate_callback )
        form->deactivate_callback( form, form->deactivate_data );

    form->deactivated++;

    if ( form->child )
        fl_deactivate_form( form->child );
}
