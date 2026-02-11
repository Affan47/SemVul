set_color_info(gx_device_color_info * pdci, DISPLAY_MODEL model,
    int nc, int depth, int maxgray, int maxcolor)
{
    pdci->num_components = pdci->max_components = nc;
    pdci->depth = depth;
    pdci->gray_index = 0;
    pdci->max_gray = maxgray;
    pdci->max_color = maxcolor;
    pdci->dither_grays = maxgray + 1;
    pdci->dither_colors = maxcolor + 1;
    pdci->separable_and_linear = GX_CINFO_UNKNOWN_SEP_LIN;
    switch (model) {
        case DISPLAY_MODEL_GRAY:
            pdci->polarity = GX_CINFO_POLARITY_ADDITIVE;
            pdci->cm_name = "DeviceGray";
            pdci->gray_index = 0;
            break;
        case DISPLAY_MODEL_RGB:
            pdci->polarity = GX_CINFO_POLARITY_ADDITIVE;
            pdci->cm_name = "DeviceRGB";
            pdci->gray_index = GX_CINFO_COMP_NO_INDEX;
            break;
        case DISPLAY_MODEL_RGBK:
            pdci->polarity = GX_CINFO_POLARITY_ADDITIVE;
            pdci->cm_name = "DeviceRGBK";
            pdci->gray_index = 3;
            break;
        case DISPLAY_MODEL_CMYK:
            pdci->polarity = GX_CINFO_POLARITY_SUBTRACTIVE;
            pdci->cm_name = "DeviceCMYK";
            pdci->gray_index = 3;
            break;
        default:
        case DISPLAY_MODEL_SEP:

            pdci->polarity = GX_CINFO_POLARITY_SUBTRACTIVE;
            pdci->cm_name = "DeviceCMYK";
            pdci->gray_index = GX_CINFO_COMP_NO_INDEX;
            break;
    }
}
