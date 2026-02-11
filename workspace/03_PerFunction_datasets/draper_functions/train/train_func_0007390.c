hawki_get_extref_file(const cpl_frameset * frameset)
{
    int iframe;
    const char     * fname = NULL;

    for(iframe = 0 ; iframe < cpl_frameset_get_size(frameset); ++iframe)
    {
        const cpl_frame  * frame;

        frame = cpl_frameset_get_frame_const(frameset, iframe);


        if(cpl_frame_get_group(frame) == CPL_FRAME_GROUP_RAW &&
           cpl_frame_get_nextensions(frame) == HAWKI_NB_DETECTORS)
        {
            fname = cpl_frame_get_filename(frame);
            return fname;
        }
    }


    for(iframe = 0 ; iframe < cpl_frameset_get_size(frameset); ++iframe)
    {
        const cpl_frame  * frame;

        frame = cpl_frameset_get_frame_const(frameset, iframe);


        if(cpl_frame_get_group(frame) == CPL_FRAME_GROUP_PRODUCT &&
           cpl_frame_get_nextensions(frame) == HAWKI_NB_DETECTORS)
        {
            fname = cpl_frame_get_filename(frame);
            return fname;
        }
    }

    fname = cpl_frame_get_filename(cpl_frameset_get_first_const(frameset));

    return fname;
}
