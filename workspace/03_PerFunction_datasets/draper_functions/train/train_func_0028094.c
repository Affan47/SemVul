hawki_utils_check_equal_int_keys
(cpl_frameset * frames, int (*func)(const cpl_propertylist *))
{
    int                iframe;
    int                value = 0;

    if(cpl_frameset_get_size(frames) < 2)
       return 1;

    for(iframe = 0; iframe < cpl_frameset_get_size(frames); ++iframe)
    {
        cpl_propertylist * header;
        header = cpl_propertylist_load(
                     cpl_frame_get_filename(
                     cpl_frameset_get_frame_const(frames, iframe)),0);
        if(iframe == 0)
            value = (func)(header);
        else
            if(value != (func)(header))
            {
                cpl_propertylist_delete(header);
                return 0;
            }
        cpl_propertylist_delete(header);
    }
    return 1;
}
