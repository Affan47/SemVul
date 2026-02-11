type_of()
    const
{
    trace(("rpt_value_fstate::type_of(this = %08lX)\n{\n", (long)this));
    if (!converted)
        convert();
    const char *result = converted->type_of();
    trace(("return \"%s\";\n", result));
    trace(("}\n"));
    return result;
}
