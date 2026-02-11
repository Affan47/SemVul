recursive_push(VALUE list, VALUE obj, VALUE paired_obj)
{
    VALUE pair_list;

    if (!paired_obj) {
	rb_hash_aset(list, obj, Qtrue);
    }
    else if ((pair_list = rb_hash_lookup2(list, obj, Qundef)) == Qundef) {
	rb_hash_aset(list, obj, paired_obj);
    }
    else {
	if (TYPE(pair_list) != T_HASH){
	    VALUE other_paired_obj = pair_list;
	    pair_list = rb_hash_new();
	    OBJ_UNTRUST(pair_list);
	    rb_hash_aset(pair_list, other_paired_obj, Qtrue);
	    rb_hash_aset(list, obj, pair_list);
	}
	rb_hash_aset(pair_list, paired_obj, Qtrue);
    }
}
