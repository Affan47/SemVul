Init_digest(void)
{
    id_reset           = rb_intern("reset");
    id_update          = rb_intern("update");
    id_finish          = rb_intern("finish");
    id_digest          = rb_intern("digest");
    id_hexdigest       = rb_intern("hexdigest");
    id_digest_length   = rb_intern("digest_length");


    rb_mDigest = rb_define_module("Digest");


    rb_define_module_function(rb_mDigest, "hexencode", rb_digest_s_hexencode, 1);


    rb_mDigest_Instance = rb_define_module_under(rb_mDigest, "Instance");


    rb_define_method(rb_mDigest_Instance, "update", rb_digest_instance_update, 1);
    rb_define_method(rb_mDigest_Instance, "<<", rb_digest_instance_update, 1);
    rb_define_private_method(rb_mDigest_Instance, "finish", rb_digest_instance_finish, 0);
    rb_define_method(rb_mDigest_Instance, "reset", rb_digest_instance_reset, 0);
    rb_define_method(rb_mDigest_Instance, "digest_length", rb_digest_instance_digest_length, 0);
    rb_define_method(rb_mDigest_Instance, "block_length", rb_digest_instance_block_length, 0);


    rb_define_method(rb_mDigest_Instance, "==", rb_digest_instance_equal, 1);
    rb_define_method(rb_mDigest_Instance, "inspect", rb_digest_instance_inspect, 0);


    rb_define_method(rb_mDigest_Instance, "new", rb_digest_instance_new, 0);
    rb_define_method(rb_mDigest_Instance, "digest", rb_digest_instance_digest, -1);
    rb_define_method(rb_mDigest_Instance, "digest!", rb_digest_instance_digest_bang, 0);
    rb_define_method(rb_mDigest_Instance, "hexdigest", rb_digest_instance_hexdigest, -1);
    rb_define_method(rb_mDigest_Instance, "hexdigest!", rb_digest_instance_hexdigest_bang, 0);
    rb_define_method(rb_mDigest_Instance, "to_s", rb_digest_instance_to_s, 0);
    rb_define_method(rb_mDigest_Instance, "length", rb_digest_instance_length, 0);
    rb_define_method(rb_mDigest_Instance, "size", rb_digest_instance_length, 0);


    rb_cDigest_Class = rb_define_class_under(rb_mDigest, "Class", rb_cObject);
    rb_define_method(rb_cDigest_Class, "initialize",  rb_digest_class_init, 0);
    rb_include_module(rb_cDigest_Class, rb_mDigest_Instance);


    rb_define_singleton_method(rb_cDigest_Class, "digest", rb_digest_class_s_digest, -1);
    rb_define_singleton_method(rb_cDigest_Class, "hexdigest", rb_digest_class_s_hexdigest, -1);

    id_metadata = rb_intern("metadata");


    rb_cDigest_Base = rb_define_class_under(rb_mDigest, "Base", rb_cDigest_Class);

    rb_define_alloc_func(rb_cDigest_Base, rb_digest_base_alloc);

    rb_define_method(rb_cDigest_Base, "initialize_copy",  rb_digest_base_copy, 1);
    rb_define_method(rb_cDigest_Base, "reset", rb_digest_base_reset, 0);
    rb_define_method(rb_cDigest_Base, "update", rb_digest_base_update, 1);
    rb_define_method(rb_cDigest_Base, "<<", rb_digest_base_update, 1);
    rb_define_private_method(rb_cDigest_Base, "finish", rb_digest_base_finish, 0);
    rb_define_method(rb_cDigest_Base, "digest_length", rb_digest_base_digest_length, 0);
    rb_define_method(rb_cDigest_Base, "block_length", rb_digest_base_block_length, 0);
}
