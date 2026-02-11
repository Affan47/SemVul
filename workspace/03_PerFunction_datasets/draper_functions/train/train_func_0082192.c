test_addchar(ibuf s)
{


    ibuf_addchar(s, '!');


    if (strcmp(ibuf_get(s), "hello world!") != 0) {
        debug("test_addchar: Mismatch, expected \"hello world!\", got: %s\n",
                ibuf_get(s));
        return 1;
    }

    debug("test_addchar: Succeeded.\n");
    return 0;
}
