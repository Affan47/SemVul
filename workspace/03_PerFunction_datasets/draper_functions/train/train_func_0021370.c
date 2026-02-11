parse_value_numeric(const gchar *in,
                                  const ObtDDParse *const parse,
                                  gboolean *error)
{
    gfloat out = 0;
    if (sscanf(in, "%f", &out) == 0)
        parse_error("Invalid numeric value", parse, error);
    return out;
}
