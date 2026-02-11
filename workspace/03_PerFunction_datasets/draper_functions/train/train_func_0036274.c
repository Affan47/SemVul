autoapply_setting_cb( FL_OBJECT * ob,
                      long        arg  FL_UNUSED_ARG )
{
    if ( ! ( auto_apply = fl_get_button( ob ) ) )
        fl_show_object( fd_attrib->applyobj );
    else
        fl_hide_object( fd_attrib->applyobj );
}
