create_orthocenter(void)
{
    _point *A, *B, *C, *val;
    double a, b, c, ca, cb, cc, d;

    C = POP(_point);
    B = POP(_point);
    A = POP(_point);
    get_mem(val, _point);
    a = distance(B, C);
    b = distance(C, A);
    c = distance(A, B);
    if (ZERO(a) || ZERO(b) || ZERO(c)) runtime_error(_("invalid triangle"));
    ca = cosine(a, b, c);
    cb = cosine(b, c, a);
    cc = cosine(c, a, b);
    if (ca == 0) {
	ca = 1; cb = 0; cc = 0;
    } else if (cb == 0) {
	ca = 0; cb = 1; cc = 0;
    } else if (cc == 0) {
	ca = 0; cb = 0; cc = 1;
    } else {
	ca = tangent(ca); cb = tangent(cb); cc = tangent(cc);
    }
    d = ca + cb + cc;
    val->x = (ca*A->x + cb*B->x + cc*C->x)/d;
    val->y = (ca*A->y + cb*B->y + cc*C->y)/d;
    PSH(val);
}
