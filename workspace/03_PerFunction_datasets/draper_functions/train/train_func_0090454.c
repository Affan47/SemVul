active_cmp(arg_a, arg_b)
    const void *arg_a;
    const void *arg_b;
{
    const struct grp *a = arg_a;
    const struct grp *b = arg_b;


    if (a == b) {

	return(0);
    }


    if (a->hostid != b->hostid) {
	if (a->hostid > b->hostid) {
	    return 1;
	} else {
	    return -1;
	}
    }


    if (a->linenum != b->linenum) {
	if (a->linenum > b->linenum) {
	    return 1;
	} else {
	    return -1;
	}
    }


    fprintf(stderr, "%s: two internal grp elements match!\n", program);
    exit(34);

}
