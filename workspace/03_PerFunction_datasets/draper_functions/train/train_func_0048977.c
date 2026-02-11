Lpairlis()
{
# line 1280 "list.d"

	object *vp, k, d;
	int narg;
	register object *DPPbase=vs_base;
#define	keys	DPPbase[0]
#define	data	DPPbase[1]
#define	a_list	DPPbase[2+0]

	narg = vs_top - vs_base;
	if (narg < 2)
		too_few_arguments();
	if (narg <= 2 + 0) {
		vs_push(Cnil);
		narg++;
	}
	if (narg > 2 + 1)
		too_many_arguments();

# line 1282 "list.d"

	vp = vs_top + 1;
	k = keys;
	d = data;
	while (!endp(k)) {
		if (endp(d))
		 FEerror(
		  "The keys ~S and the data ~S are not of the same length",
		  2, keys, data);
		vs_check_push(make_cons(k->c.c_car, d->c.c_car));
		k = k->c.c_cdr;
		d = d->c.c_cdr;
	}
	if (!endp(d))
	    FEerror("The keys ~S and the data ~S are not of the same length",
		    2, keys, data);
	vs_push(a_list);
	while (vs_top > vp)
		stack_cons();
	{
		vs_base[0] = vp[-1];
		vs_top = vs_base + 1;
		return;
	}
# line 1301 "list.d"

#undef keys
#undef data
#undef a_list
}
