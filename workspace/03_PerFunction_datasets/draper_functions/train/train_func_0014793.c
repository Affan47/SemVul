fl_activate_form( FL_FORM * form )
{
    if ( ! form )
    {
        M_err( "fl_activate_form", "NULL form" );
        return;
    }

    if ( form->deactivated )
    {
        form->deactivated--;

        if ( ! form->deactivated && form->activate_callback )
            form->activate_callback( form, form->activate_data );
    }

    if ( form->child )
        fl_activate_form( form->child );
}
