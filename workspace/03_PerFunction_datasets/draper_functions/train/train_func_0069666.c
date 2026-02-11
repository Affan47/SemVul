isaac64_selftest(void)
{
    isaac64_context ctx;
    uint8_t stream[sizeof isaac64_test_keystream];
    size_t n;
    bool failed = false;

    isaac64_init(&ctx, isaac64_test_key);
    isaac64_gen_keystream(&ctx, RANDSIZB, stream,
                          sizeof isaac64_test_keystream);
    for (n = 0; n < sizeof isaac64_test_keystream; n++)
        if (isaac64_test_keystream[n] != stream[n])
        {
            fprintf(stderr,
                    "FAIL: isaac64: offset %zu exp %02x got %02x\n",
                    n, isaac64_test_keystream[n], stream[n]);
            failed = true;
        }

    if (failed)
        abort();
}
