alloc(size_t amount)
{
    if (amount == 0) {

        long chunksize;
        char *nmem;


        if ((chunksize = get_pagesize()) == -1)
            chunksize = 1024;

        nmem = malloc(amount);
        do {
            amount += chunksize;
            mem = nmem;
            nmem = realloc(mem, amount);
        } while (nmem != NULL);
        amount -= chunksize;
        if (verbose != 0)
            fprintf(stderr, "allocated %lu bytes of memory\n",
                (unsigned long)amount);
    } else {

        if (((mem = malloc(amount)) == NULL) && (amount > 0)) {
            fprintf(stderr, "not enough memory\n");
            exit(EXIT_FAILURE);
        }
    }
    return amount;
}
