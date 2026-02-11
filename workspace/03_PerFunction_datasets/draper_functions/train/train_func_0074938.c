Init_iconv(void)
{
    VALUE rb_cIconv = rb_define_class("Iconv", rb_cData);

    if (!NIL_P(ruby_verbose)) {
	warn_deprecated();
    }
    rb_define_alloc_func(rb_cIconv, iconv_s_allocate);
    rb_define_singleton_method(rb_cIconv, "open", iconv_s_open, -1);
    rb_define_singleton_method(rb_cIconv, "iconv", iconv_s_iconv, -1);
    rb_define_singleton_method(rb_cIconv, "conv", iconv_s_conv, 3);
    rb_define_singleton_method(rb_cIconv, "list", iconv_s_list, 0);
    rb_define_singleton_method(rb_cIconv, "ctlmethods", iconv_s_ctlmethods, 0);
    rb_define_method(rb_cIconv, "initialize", iconv_initialize, -1);
    rb_define_method(rb_cIconv, "close", iconv_finish, 0);
    rb_define_method(rb_cIconv, "iconv", iconv_iconv, -1);
    rb_define_method(rb_cIconv, "conv", iconv_conv, -1);
    rb_define_method(rb_cIconv, "trivial?", iconv_trivialp, 0);
    rb_define_method(rb_cIconv, "transliterate?", iconv_get_transliterate, 0);
    rb_define_method(rb_cIconv, "transliterate=", iconv_set_transliterate, 1);
    rb_define_method(rb_cIconv, "discard_ilseq?", iconv_get_discard_ilseq, 0);
    rb_define_method(rb_cIconv, "discard_ilseq=", iconv_set_discard_ilseq, 1);

    rb_eIconvFailure = rb_define_module_under(rb_cIconv, "Failure");
    rb_define_method(rb_eIconvFailure, "initialize", iconv_failure_initialize, 3);
    rb_define_method(rb_eIconvFailure, "success", iconv_failure_success, 0);
    rb_define_method(rb_eIconvFailure, "failed", iconv_failure_failed, 0);
    rb_define_method(rb_eIconvFailure, "inspect", iconv_failure_inspect, 0);

    rb_eIconvInvalidEncoding = rb_define_class_under(rb_cIconv, "InvalidEncoding", rb_eArgError);
    rb_eIconvIllegalSeq = rb_define_class_under(rb_cIconv, "IllegalSequence", rb_eArgError);
    rb_eIconvInvalidChar = rb_define_class_under(rb_cIconv, "InvalidCharacter", rb_eArgError);
    rb_eIconvOutOfRange = rb_define_class_under(rb_cIconv, "OutOfRange", rb_eRuntimeError);
    rb_eIconvBrokenLibrary = rb_define_class_under(rb_cIconv, "BrokenLibrary", rb_eRuntimeError);
    rb_include_module(rb_eIconvInvalidEncoding, rb_eIconvFailure);
    rb_include_module(rb_eIconvIllegalSeq, rb_eIconvFailure);
    rb_include_module(rb_eIconvInvalidChar, rb_eIconvFailure);
    rb_include_module(rb_eIconvOutOfRange, rb_eIconvFailure);
    rb_include_module(rb_eIconvBrokenLibrary, rb_eIconvFailure);

    rb_success = rb_intern("success");
    rb_failed = rb_intern("failed");
    id_transliterate = rb_intern("transliterate");
    id_discard_ilseq = rb_intern("discard_ilseq");

    rb_gc_register_address(&charset_map);
    charset_map = rb_hash_new();
    rb_define_singleton_method(rb_cIconv, "charset_map", charset_map_get, 0);
}
