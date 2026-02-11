unpack_disposition(ParseContext *context)
{
    Octstr *decoded = NULL;
    int selector;

    selector = parse_get_char(context) - 128;
    decoded = wsp_disposition_to_string(selector);
    if (!decoded) {
        warning(0, "Cannot parse content-disposition value.");
        return NULL;
    }
    wsp_unpack_all_parameters(context, decoded);
    return decoded;
}
