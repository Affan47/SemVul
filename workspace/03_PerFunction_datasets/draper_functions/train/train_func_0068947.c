write_ifiction_xlat_base(synthctx *ctx, int indent,
                                     const char *gameinfo_key,
                                     const char *ifiction_tag,
                                     const char *dflt, int html)
{
    valinfo *val;
    const char *valstr;
    size_t vallen;


    if ((val = find_by_key(ctx->vals, gameinfo_key)) != 0)
    {

        valstr = val->val;
        vallen = val->val_len;
    }
    else if (dflt != 0)
    {

        valstr = dflt;
        vallen = strlen(dflt);
    }
    else
    {

        return;
    }


    while (indent != 0)
    {
        static const char spaces[] = "          ";
        size_t cur;


        cur = indent;
        if (cur > sizeof(spaces) - 1)
            cur = sizeof(spaces) - 1;


        write_ifiction(ctx, spaces, cur);


        indent -= cur;
    }


    write_ifiction_z(ctx, "<");
    write_ifiction_z(ctx, ifiction_tag);
    write_ifiction_z(ctx, ">");


    if (html)
        write_ifiction(ctx, valstr, vallen);
    else
        write_ifiction_pcdata(ctx, valstr, vallen);


    write_ifiction_z(ctx, "</");
    write_ifiction_z(ctx, ifiction_tag);
    write_ifiction_z(ctx, ">\n");
}
