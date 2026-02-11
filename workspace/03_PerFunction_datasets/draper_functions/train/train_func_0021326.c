f_ellip_second(union argument *arg)
{
    struct value a;
    double	ak,q,e;

    (void) arg;
    (void) pop(&a);
    if (fabs(imag(&a)) > zero)
	int_error(NO_CARET, "can only do elliptic integrals of reals");

    ak=real(&a);
    q=(1.0-ak)*(1.0+ak);
    if (q > 0.0) {
	e=carlson_elliptic_rf(0.0,q,1.0)-(ak*ak)*carlson_elliptic_rd(0.0,q,1.0)/3.0;
	push(Gcomplex(&a,e,0.0));

    } else if (q < 0.0) {
	undefined=TRUE;
	push(&a);

    } else {
	e=1.0;
	push(Gcomplex(&a,e,0.0));
    }


}
