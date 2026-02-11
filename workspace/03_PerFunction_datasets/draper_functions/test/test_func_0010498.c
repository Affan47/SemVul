rb_hash_initialize(int argc, VALUE *argv, VALUE hash)
{
    VALUE ifnone;

    rb_hash_modify(hash);
    if (rb_block_given_p()) {
	if (argc > 0) {
	    rb_raise(rb_eArgError, "wrong number of arguments");
	}
	ifnone = rb_block_proc();
	default_proc_arity_check(ifnone);
	RHASH_IFNONE(hash) = ifnone;
	FL_SET(hash, HASH_PROC_DEFAULT);
    }
    else {
	rb_scan_args(argc, argv, "01", &ifnone);
	RHASH_IFNONE(hash) = ifnone;
    }

    return hash;
}
