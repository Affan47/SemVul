reconstruct_lhs(const match_ty *mp, string_ty *lhs, const expr_position_ty *pp)
{
    const match_regex_ty *this;
    static stracc   buffer;
    int             depth;
    int             n;
    char            *cp;
    char            *ip;
    string_ty       *s;
    int             j;

    trace(("match_regex::reconstruct_lhs(mp = %p, lhs = %p)\n{\n", mp, lhs));
    this = (const match_regex_ty *)mp;
    trace_string(lhs->str_text);

    assert(this->actual);
    if (!this->actual)
    {

        trace(("}\n"));
        return 0;
    }
    ip = this->actual->str_text;

    sa_open(&buffer);

    depth = 0;
    n = 0;
    for (cp = lhs->str_text; *cp; ++cp)
    {
        const regmatch_t *rm;

        switch (*cp)
        {
        default:
            if (depth == 0)
                sa_char(&buffer, *cp);
            break;

        case '\\':
            switch (*++cp)
            {
            default:
                if (depth == 0)
                    sa_char(&buffer, *cp);
                break;

            case '(':
                ++depth;
                ++n;
                if (depth == 1)
                {
                    rm = &this->match[n];
                    if (rm->rm_so < 0)
                    {
                        illegal_sub_expr(pp, lhs, n);
                        trace(("return NULL;\n"));
                        trace(("}\n"));
                        return 0;
                    }
                    sa_chars(&buffer, ip + rm->rm_so, rm->rm_eo - rm->rm_so);
                }
                break;

            case ')':
                if (depth > 0)
                    --depth;
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (depth == 0)
                {
                    j = *cp - '0';
                    rm = &this->match[j];
                    if (rm->rm_so < 0)
                    {
                        illegal_sub_expr(pp, lhs, j);
                        trace(("return NULL;\n"));
                        trace(("}\n"));
                        return 0;
                    }
                    sa_chars(&buffer, ip + rm->rm_so, rm->rm_eo - rm->rm_so);
                }
                break;

            case 0:
                --cp;
                break;
            }
            break;
        }
    }

    s = sa_close(&buffer);
    trace_string(s->str_text);
    trace(("return %p;\n", s));
    trace(("}\n"));
    return s;
}
