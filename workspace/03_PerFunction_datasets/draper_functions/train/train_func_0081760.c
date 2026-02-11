test_rw_u32(tst_case *tc, void *data)
{
    int i;
    Store *store = (Store *)data;
    f_u32 uints[4] = { POSH_U32_MAX, POSH_U32_MIN, 100000, 1 };
    OutStream *ostream = store->new_output(store, "rw_uint.test");
    InStream *istream;

    for (i = 0; i < 4; i++) {
        os_write_u32(ostream, uints[i]);
    }
    os_close(ostream);

    istream = store->open_input(store, "rw_uint.test");
    for (i = 0; i < 4; i++) {
        Aiequal(uints[i], is_read_u32(istream));
    }
    is_close(istream);
    Aiequal(16, store->length(store, "rw_uint.test"));
}
