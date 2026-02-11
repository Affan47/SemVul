s_real_color_changed(GdkRGBA & gdkcolor, AP_UnixDialog_Options * dlg)
{

	UT_RGBColor * rgbcolor = UT_UnixGdkColorToRGBColor(gdkcolor);
	UT_HashColor hash_color;
    strncpy ( dlg->m_CurrentTransparentColor, hash_color.setColor(*rgbcolor), 9 );

    UT_DEBUGMSG ( ( "Changing Color [%s]\n", hash_color.c_str() ) );
	delete rgbcolor;

    if ( strcmp ( dlg->m_CurrentTransparentColor, "#ffffff" ) == 0 )
        gtk_widget_set_sensitive ( dlg->m_buttonColSel_Defaults, FALSE );
    else
        gtk_widget_set_sensitive ( dlg->m_buttonColSel_Defaults, TRUE );


    s_control_changed ( dlg->m_pushbuttonNewTransparentColor, dlg );
}
