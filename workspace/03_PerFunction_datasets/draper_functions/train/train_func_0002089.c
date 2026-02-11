main(void)
{
    int rv = 0;

    printf("-- speed tests determine parsing throughput given %d different sample documents --\n",
           num_docs());

    rv = parse(1);
    if (rv != 0) return rv;
    rv = parse(0);
    if (rv != 0) return rv;
    rv = gen();

    return rv;
}
