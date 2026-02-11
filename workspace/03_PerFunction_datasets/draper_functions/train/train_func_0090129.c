radius_type_convert(int type, Octstr *value)
{
    Octstr *ret = NULL;
    int i;

    switch (type) {
        case t_int:
            ret = octstr_format("%ld", decode_integer(value, 0, 4));
            break;
        case t_string:
            ret = octstr_format("%s", octstr_get_cstr(value));
            break;
        case t_ipaddr:
            ret = octstr_create("");
            for (i = 0; i < 4; i++) {
                int c = octstr_get_char(value, i);
                Octstr *b = octstr_format("%d", c);
                octstr_append(ret, b);
                if (i < 3)
                    octstr_append_cstr(ret, ".");
                octstr_destroy(b);
            }
            break;
        default:
            panic(0, "RADIUS: Attribute type %d does not exist.", type);
            break;
    }

    return ret;
}
