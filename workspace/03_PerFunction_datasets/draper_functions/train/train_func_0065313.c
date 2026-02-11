rb_hash_update_by(VALUE hash1, VALUE hash2, rb_hash_update_func *func)
{
    rb_hash_modify(hash1);
    hash2 = to_hash(hash2);
    if (func) {
	struct update_arg arg;
	arg.hash = hash1;
	arg.func = func;
	rb_hash_foreach(hash2, rb_hash_update_func_i, (VALUE)&arg);
    }
    else {
	rb_hash_foreach(hash2, rb_hash_update_i, hash1);
    }
    return hash1;
}
