cpl_vector_gen_lowpass_kernel(
        cpl_lowpass filt_type,
        cpl_size    hw)
{
    cpl_vector * kernel;
    double       norm;
    cpl_size     i;


    cpl_ensure(hw >= 0, CPL_ERROR_ILLEGAL_INPUT, NULL);


    kernel = cpl_vector_new(2*hw+1);
    switch(filt_type) {
        case CPL_LOWPASS_LINEAR:

            for (i=-hw; i<=hw; i++) kernel->data[hw+i] = 1.0/(double)(2*hw+1);
            break;
        case CPL_LOWPASS_GAUSSIAN:
            norm = 0.00;
            for (i=-hw; i < 1 + hw; i++) {

                kernel->data[hw+i] = exp(-(double)(i*i));
                norm += kernel->data[hw+i];
            }
            for (i = 0; i<2*hw+1; i++) kernel->data[i] /= norm;
            cpl_tools_add_flops(2*hw*4);
            break;
        default:

            kernel = NULL;
            (void)cpl_error_set_(CPL_ERROR_INVALID_TYPE);
            break;
    }
    return kernel;
}
