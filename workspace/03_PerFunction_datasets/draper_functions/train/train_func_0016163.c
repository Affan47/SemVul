cgwop_tostr(struct cgwop *cgwop)
{
    int len = cgwop->num_fields;
    Octstr *str;

    if (cgw_ops[cgwop->op] == NULL) return NULL;

    str = octstr_create("");

    octstr_append(str, octstr_imm("op:"));
    octstr_append(str, octstr_imm(cgw_ops[cgwop->op]));
    octstr_append_char(str, CGW_EOL);

    while (--len >= 0)
    {
        octstr_append(str, cgwop->name[len]);
        octstr_append_char(str, ':');
        octstr_append(str, cgwop->value[len]);
        octstr_append_char(str, CGW_EOL);
    }
    octstr_append(str, octstr_imm("end:"));
    octstr_append(str, octstr_imm(cgw_ops[cgwop->op]));
    octstr_append_char(str, CGW_EOL);

    return str;
}
