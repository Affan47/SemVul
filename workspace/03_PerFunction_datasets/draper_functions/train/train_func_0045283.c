Perl_hv_delete(pTHX_ HV *hv, const char *key, I32 klen_i32, I32 flags)
{
    STRLEN klen;
    int k_flags;

    PERL_ARGS_ASSERT_HV_DELETE;

    if (klen_i32 < 0) {
	klen = -klen_i32;
	k_flags = HVhek_UTF8;
    } else {
	klen = klen_i32;
	k_flags = 0;
    }
    return MUTABLE_SV(hv_common(hv, NULL, key, klen, k_flags, flags | HV_DELETE,
				NULL, 0));
}
