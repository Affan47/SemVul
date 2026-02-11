set_inference_override(CdlValueSource source)
{
    CYG_REPORT_FUNCNAME("CdlTransaction::set_inference_override");
    CYG_REPORT_FUNCARG1XV(source);
    CYG_PRECONDITIONC((CdlValueSource_Invalid == source) || Cdl::is_valid_value_source(source));

    inference_override = source;

    CYG_REPORT_RETURN();
}
