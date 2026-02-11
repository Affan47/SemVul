bifink(bifcxdef *ctx, int argc)
{
    int    c;
    int    extc;
    char   str[20];
    size_t len;

    bifcntargs(ctx, 0, argc);
    tioflushn(ctx->bifcxtio, 0);


    c = os_getc_raw();


    extc = (c == 0 ? os_getc_raw() : 0);


    get_ext_key_name(str, c, extc);


    len = strlen(str);


    outreset();


    runpstr(ctx->bifcxrun, str, len, 0);
}
