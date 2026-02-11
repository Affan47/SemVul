billterm_ns(FILE *out)
{
    g_return_val_if_fail(out, FALSE);
    return
        gnc_xml2_write_namespace_decl(out, "billterm")
        && gnc_xml2_write_namespace_decl(out, "bt-days")
        && gnc_xml2_write_namespace_decl(out, "bt-prox");
}
