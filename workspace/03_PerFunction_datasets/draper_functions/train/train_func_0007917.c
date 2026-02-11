fl_get_app_resources( FL_resource * appresource,
                      int           n )
{
    char *tmp = fl_app_name;

    fl_app_name = fl_ori_app_name;
    fli_get_app_resource( appresource, n );

    if ( fl_app_name != tmp )
    {
        fl_app_name = tmp;
        fli_get_app_resource( appresource, n );
    }
}
