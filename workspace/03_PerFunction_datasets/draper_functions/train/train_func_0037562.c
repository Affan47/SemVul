H5S_debug(H5F_t *f, hid_t dxpl_id, const void *_mesg, FILE *stream, int indent,
    int fwidth)
{
    const H5S_t	*mesg = (const H5S_t*)_mesg;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    switch(H5S_GET_EXTENT_TYPE(mesg)) {
        case H5S_NULL:
            fprintf(stream, "%*s%-*s H5S_NULL\n", indent, "", fwidth,
                    "Space class:");
            break;

        case H5S_SCALAR:
            fprintf(stream, "%*s%-*s H5S_SCALAR\n", indent, "", fwidth,
                    "Space class:");
            break;

        case H5S_SIMPLE:
            fprintf(stream, "%*s%-*s H5S_SIMPLE\n", indent, "", fwidth,
                    "Space class:");
            H5O_debug_id(H5O_SDSPACE_ID, f, dxpl_id, &(mesg->extent), stream,
                                 indent + 3, MAX(0, fwidth - 3));
            break;

        default:
            fprintf(stream, "%*s%-*s **UNKNOWN-%ld**\n", indent, "", fwidth,
                    "Space class:", (long)(H5S_GET_EXTENT_TYPE(mesg)));
            break;
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
