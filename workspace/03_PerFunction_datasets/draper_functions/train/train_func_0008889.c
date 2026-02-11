fput_sem_node_ope(FILE *fp, qr_operator ope)
{
    char *str;

    switch (ope) {
    case OPE_ADD: str = "+"; break;
    case OPE_SUB: str = "-"; break;
    case OPE_MUL: str = "*"; break;
    case OPE_DIV: str = "/"; break;
    case OPE_POWER: str = "^"; break;
    case OPE_INTFUNC: str = ((flg_cmp_f) || (flg_cmp_c))
                          ? ""
                          : str_ope[ope]; break;
    default:
        str = str_ope[ope];
    }

    return fprintf(fp, "%s", str);
}
