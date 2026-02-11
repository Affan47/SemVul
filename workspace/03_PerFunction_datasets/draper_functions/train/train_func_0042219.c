memtest_non_destructive_invert(void *addr, size_t size) {
    volatile unsigned long *p = addr;
    size_t words = size / sizeof(unsigned long);
    size_t j;


    for (j = 0; j < words; j++)
        p[j] = ~p[j];
}
