validate_cache_size(unsigned long long cache_size)
{
    long nr_pages = 0;
    unsigned long long ram_size;
    if(cache_size > IO_CACHE_MAX_SIZE)
    {
        log_error("Cache size [%lld] exceeds max allowed cache size [%lld]\n",
                  cache_size, IO_CACHE_MAX_SIZE);
        return -1;
    }
    nr_pages = sysconf(_SC_PHYS_PAGES);
    if(nr_pages < 0) return 0;
    ram_size = nr_pages * getpagesize();
    if(cache_size * 2 > ram_size)
    {
        log_error("Cache size [%lld] is greater than twice of available ram size [%lld] bytes\n",
                  cache_size, ram_size);
        return -1;
    }
    return 0;
}
