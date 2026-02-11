hawki_load_extensions
(const cpl_frameset  *   fset,
 int                     extension,
 cpl_type                ptype)
{
    int                     nframes ;
    cpl_imagelist       *   out ;
    const cpl_frame     *   frame ;
    const char          *   fname ;
    cpl_image           *   ima ;
    int                     iframe;


    if (fset == NULL) return NULL ;
    nframes = cpl_frameset_get_size(fset) ;


    out = cpl_imagelist_new() ;


    for (iframe=0 ; iframe<nframes ; iframe++) {


        frame = cpl_frameset_get_frame_const(fset, iframe) ;
        fname = cpl_frame_get_filename(frame) ;


        if ((ima=cpl_image_load(fname, ptype, 0, extension)) == NULL) {
            cpl_msg_error(__func__, "Cannot load %dth frame (extension %d)",
                    iframe+1, extension) ;
            cpl_imagelist_delete(out) ;
            return NULL ;
        }
        cpl_imagelist_set(out, ima, iframe) ;
    }
    return out ;
}
