fl_scale_form( FL_FORM * form,
               double    xsc,
               double    ysc )
{
    if ( ! form )
    {
        M_err( "fl_scale_form", "NULL form" );
        return;
    }

    if (    FL_crnd( form->w_hr * xsc ) == form->w
         && FL_crnd( form->h_hr * ysc ) == form->h )
        return;

    fli_scale_form( form, xsc, ysc );


    if ( form->visible == FL_VISIBLE )
        fl_winresize( form->window, form->w, form->h );
}
