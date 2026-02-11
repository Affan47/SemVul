convolution_filter_set_value(ConvolutionControls *controls,
                             guint j,
                             guint i,
                             gdouble val)
{
    ConvolutionFilterSymmetryType hsym, vsym;
    guint size;

    size = controls->args->preset->data.size;
    hsym = controls->args->preset->hsym;
    vsym = controls->args->preset->vsym;

    convolution_filter_do_set_value(controls, j, i, val);
    if (hsym == CONVOLUTION_FILTER_SYMMETRY_EVEN) {
        convolution_filter_do_set_value(controls, size-1-j, i, val);
        if (vsym == CONVOLUTION_FILTER_SYMMETRY_EVEN) {
            convolution_filter_do_set_value(controls, j, size-1-i, val);
            convolution_filter_do_set_value(controls, size-1-j, size-1-i, val);
        }
        else if (vsym == CONVOLUTION_FILTER_SYMMETRY_ODD) {
            convolution_filter_do_set_value(controls, j, size-1-i, -val);
            convolution_filter_do_set_value(controls, size-1-j, size-1-i, -val);
        }
    }
    else if (hsym == CONVOLUTION_FILTER_SYMMETRY_ODD) {
        convolution_filter_do_set_value(controls, size-1-j, i, -val);
        if (vsym == CONVOLUTION_FILTER_SYMMETRY_EVEN) {
            convolution_filter_do_set_value(controls, j, size-1-i, val);
            convolution_filter_do_set_value(controls, size-1-j, size-1-i, -val);
        }
        else if (vsym == CONVOLUTION_FILTER_SYMMETRY_ODD) {
            convolution_filter_do_set_value(controls, j, size-1-i, -val);
            convolution_filter_do_set_value(controls, size-1-j, size-1-i, val);
        }
    }
    else {
        if (vsym == CONVOLUTION_FILTER_SYMMETRY_EVEN)
            convolution_filter_do_set_value(controls, j, size-1-i, val);
        else if (vsym == CONVOLUTION_FILTER_SYMMETRY_ODD)
            convolution_filter_do_set_value(controls, j, size-1-i, -val);
    }
}
