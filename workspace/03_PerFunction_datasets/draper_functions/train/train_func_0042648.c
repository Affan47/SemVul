test_refstr_create(void)
{
    H5RS_str_t *rs;
    unsigned count;
    herr_t ret;


    MESSAGE(5, ("Testing Creating & Closing Ref-Counted Strings\n"));


    rs=H5RS_create("foo");
    CHECK(rs, NULL, "H5RS_create");


    count=H5RS_get_count(rs);
    VERIFY(count, 1, "H5RS_get_count");


    ret=H5RS_decr(rs);
    CHECK(ret, FAIL, "H5RS_decr");

}
