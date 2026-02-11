FAPI_FF_get_name(gs_fapi_font *ff, gs_fapi_font_feature var_id, int index,
                 char *Buffer, int len)
{
    ref name, string;
    ref *pdr = pfont_dict(((gs_font_base *) ff->client_font_data2));

    switch ((int)var_id) {
        case gs_fapi_font_feature_BlendAxisTypes:
            {
                ref *Info, *Axes;

                if (dict_find_string(pdr, "FontInfo", &Info) <= 0)
                    return 0;
                if (dict_find_string(Info, "BlendAxisTypes", &Axes) <= 0)
                    return 0;
                if (!r_has_type(Axes, t_array))
                    return 0;
                if (array_get(ff->memory, Axes, index, &name) < 0)
                    return 0;
            }
    }
    name_string_ref(ff->memory, &name, &string);
    if (r_size(&string) >= len)
        return 0;
    memcpy(Buffer, string.value.const_bytes, r_size(&string));
    Buffer[r_size(&string)] = 0x00;
    return 1;
}
