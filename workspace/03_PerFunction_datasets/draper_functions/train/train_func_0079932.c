is_quadrangle_color_linear_by_diagonals(const patch_fill_state_t *pfs, const quadrangle_patch *p)
{
    int code;

    code = is_color_linear(pfs, p->p[0][0]->c, p->p[1][1]->c);
    if (code <= 0)
        return code;
    return is_color_linear(pfs, p->p[0][1]->c, p->p[1][0]->c);
}
