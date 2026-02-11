wsp_pack_text(Octstr *packed, Octstr *text)
{


    if (octstr_get_char(text, 0) >= 128 || octstr_get_char(text, 0) < 32)
        octstr_append_char(packed, WSP_QUOTE);
    octstr_append(packed, text);
    octstr_append_char(packed, 0);
    return 0;
}
