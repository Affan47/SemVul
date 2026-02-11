compress_gzip_open(void)
{


    if ( 0 != mca_compress_gzip_component.super.verbose) {
        mca_compress_gzip_component.super.output_handle = opal_output_open(NULL);
        opal_output_set_verbosity(mca_compress_gzip_component.super.output_handle,
                                  mca_compress_gzip_component.super.verbose);
    } else {
        mca_compress_gzip_component.super.output_handle = opal_compress_base_framework.framework_output;
    }


    opal_output_verbose(10, mca_compress_gzip_component.super.output_handle,
                        "compress:gzip: open()");
    opal_output_verbose(20, mca_compress_gzip_component.super.output_handle,
                        "compress:gzip: open: priority = %d",
                        mca_compress_gzip_component.super.priority);
    opal_output_verbose(20, mca_compress_gzip_component.super.output_handle,
                        "compress:gzip: open: verbosity = %d",
                        mca_compress_gzip_component.super.verbose);
    return OPAL_SUCCESS;
}
