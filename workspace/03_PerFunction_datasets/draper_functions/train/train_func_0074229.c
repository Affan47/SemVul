H5O_sdspace_debug(H5F_t UNUSED *f, hid_t UNUSED dxpl_id, const void *mesg,
		  FILE * stream, int indent, int fwidth)
{
    const H5S_extent_t	   *sdim = (const H5S_extent_t *)mesg;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(f);
    HDassert(sdim);
    HDassert(stream);
    HDassert(indent >= 0);
    HDassert(fwidth >= 0);

    HDfprintf(stream, "%*s%-*s %lu\n", indent, "", fwidth,
	    "Rank:",
	    (unsigned long) (sdim->rank));

    if(sdim->rank > 0) {
        unsigned		    u;

        HDfprintf(stream, "%*s%-*s {", indent, "", fwidth, "Dim Size:");
        for(u = 0; u < sdim->rank; u++)
            HDfprintf (stream, "%s%Hu", u?", ":"", sdim->size[u]);
        HDfprintf (stream, "}\n");

        HDfprintf(stream, "%*s%-*s ", indent, "", fwidth, "Dim Max:");
        if(sdim->max) {
            HDfprintf (stream, "{");
            for(u = 0; u < sdim->rank; u++) {
                if(H5S_UNLIMITED==sdim->max[u])
                    HDfprintf (stream, "%sINF", u?", ":"");
                else
                    HDfprintf (stream, "%s%Hu", u?", ":"", sdim->max[u]);
            }
            HDfprintf (stream, "}\n");
        }
        else
            HDfprintf (stream, "CONSTANT\n");
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
