create_perpendicular_to_segment(void)
{
    _set *seg;
    _point *O, *A, *B;
    double a;
    _line *val;

    O = POP(_point);
    seg = POP(_set);
    A = get_point(&seg);
    B = get_point(&seg);
    if (EQL(A->x, B->x) && EQL(A->y, B->y)) runtime_error(_("invalid segment"));
    a = argument(A, B);
    get_mem(val, _line);
    val->x = O->x;
    val->y = O->y;
    val->a = a + (a<=90 ? 90 : -270);
    PSH(val);
}
