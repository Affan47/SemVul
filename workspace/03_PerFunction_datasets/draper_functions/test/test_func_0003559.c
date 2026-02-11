eb_wide_font_xpm_size(EB_Font_Code height, size_t *size)
{
    EB_Error_Code error_code;

    LOG(("in: eb_wide_font_xpm_size(height=%d)", (int)height));

    switch (height) {
    case EB_FONT_16:
        *size = EB_SIZE_WIDE_FONT_16_XPM;
	break;
    case EB_FONT_24:
        *size = EB_SIZE_WIDE_FONT_24_XPM;
	break;
    case EB_FONT_30:
        *size = EB_SIZE_WIDE_FONT_30_XPM;
	break;
    case EB_FONT_48:
        *size = EB_SIZE_WIDE_FONT_48_XPM;
	break;
    default:
	error_code = EB_ERR_NO_SUCH_FONT;
	goto failed;
    }

    LOG(("out: eb_wide_font_xpm_size(size=%ld) = %s", (long)*size,
	eb_error_string(EB_SUCCESS)));

    return EB_SUCCESS;


  failed:
    *size = 0;
    LOG(("out: eb_wide_font_xpm_size() = %s", eb_error_string(error_code)));
    return error_code;
}
