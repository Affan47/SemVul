test_buffer_seek(tst_case *tc, void *data)
{
    int i;
    Store *store = (Store *)data;

    OutStream *ostream = store->new_output(store, "rw_seek.test");
    char text[60] = "This is another int test string !@#$%#$%&%$*%^&*()(_";
    InStream *istream;

    for (i = 0; i < 1000; i++) {
        os_write_i64(ostream, i);
        os_write_string(ostream, text);
    }
    os_seek(ostream, 987);
    Aiequal(987, os_pos(ostream));
    os_write_vint(ostream, 555);
    os_seek(ostream, 56);
    Aiequal(56, os_pos(ostream));
    os_write_vint(ostream, 12345);
    os_seek(ostream, 4000);
    Aiequal(4000, os_pos(ostream));
    os_write_voff_t(ostream, 98763210);
    os_close(ostream);

    istream = store->open_input(store, "rw_seek.test");
    is_seek(istream, 56);
    Aiequal(56, is_pos(istream));
    Aiequal(12345, is_read_vint(istream));
    is_seek(istream, 4000);
    Aiequal(4000, is_pos(istream));
    Aiequal(98763210, is_read_voff_t(istream));
    is_seek(istream, 987);
    Aiequal(987, is_pos(istream));
    Aiequal(555, is_read_vint(istream));
    is_close(istream);
}
