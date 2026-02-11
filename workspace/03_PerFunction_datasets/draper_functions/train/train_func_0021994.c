rb_ary_unshare_safe(VALUE ary)
{
    if (ARY_SHARED_P(ary) && !ARY_EMBED_P(ary)) {
	rb_ary_unshare(ary);
    }
}
