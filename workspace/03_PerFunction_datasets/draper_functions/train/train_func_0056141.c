read( t_CKINT element_type, t_CKINT element_num, HidMsg * msg )
{
    if( !default_drivers[device_type].read )
    {
        EM_log( CK_LOG_WARNING,
                "PhyHidDevIn: read() failed -> %s does not support read",
                default_drivers[device_type].driver_name );
        return FALSE;
    }

    if( default_drivers[device_type].read( device_num, element_type,
                                           element_num, msg ) )
    {
        EM_log( CK_LOG_WARNING,
                "PhyHidDevIn: read() failed for %s %i, element type %i, element number %i",
                default_drivers[device_type].driver_name, device_num,
                element_type, element_num );
        return FALSE;
    }

    return TRUE;
}
