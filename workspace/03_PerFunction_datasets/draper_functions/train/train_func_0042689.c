rpermute0(long n, long r, long *p, long index, VALUE values)
{
    long i, j;
    for (i = 0; i < n; i++) {
	p[index] = i;
	if (index < r-1) {
	    rpermute0(n, r, p, index+1, values);
	}
	else {


	    VALUE result = rb_ary_new2(r);
	    VALUE *result_array = RARRAY_PTR(result);
	    const VALUE *values_array = RARRAY_PTR(values);

	    for (j = 0; j < r; j++) result_array[j] = values_array[p[j]];
	    ARY_SET_LEN(result, r);
	    rb_yield(result);
	    if (RBASIC(values)->klass) {
		rb_raise(rb_eRuntimeError, "repeated permute reentered");
	    }
	}
    }
}
