aset_add(node A, int R, node point)
{
    node ptr = A;
    LOCS(1);
    PUSH_LOC(A);
    if (A == 0)
	bad_error("Null Aset in aset_add()");
    if (point == 0)
	bad_error("Null point in aset_add()");
    if (R >= 1 && R(A) >= R) {
	ptr = St(A);
	while ((R--) > 0)
	    ptr = Cdr(ptr);
	pcfg_add(point, Car(ptr));
    } else
	bad_error("index out of bounds in aset_add()");
    POP_LOCS();
    return 1;
}
