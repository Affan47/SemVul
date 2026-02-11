chk_ETag(void)
{
    const char *etag, *etag1;
    do_put_return_ETag("resETag", "test_contents");
    etag=resETag;
    do_put_return_ETag("resETag", "test_contents1");
    etag1=resETag;
    if (strcmp(etag,etag1) ==0)
	t_warning("resource changed. Etag should have changed. %s , %s",etag, etag1);

    return OK;
}
