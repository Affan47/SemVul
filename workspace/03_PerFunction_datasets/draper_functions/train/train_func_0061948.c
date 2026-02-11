test_rw_i64(tst_case *tc, void *data)
{
    int i;
    Store *store = (Store *)data;
    f_u64 longs[4] =
        { POSH_I64_MIN, POSH_I64_MAX, POSH_I64(-1), POSH_I64(0) };
    OutStream *ostream = store->new_output(store, "rw_long.test");
    InStream *istream;

    for (i = 0; i < 4; i++) {
        os_write_i64(ostream, longs[i]);
    }
    os_close(ostream);

    istream = store->open_input(store, "rw_long.test");
    for (i = 0; i < 4; i++) {
        Aiequal(longs[i], is_read_i64(istream));
    }
    is_close(istream);
    Aiequal(32, store->length(store, "rw_long.test"));
}
