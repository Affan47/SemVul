testrealloc(void* p,yy_size_t n ,void* yyscanner)
{
    int i;
    for (i=0; i < arrsz; i++)
        if ( ptrs[i].p == p){
            total_mem -= ptrs[i].sz;
            total_mem += n;
            ptrs[i].p = (void*)realloc(p,n);
            ptrs[i].sz = n;

            printf("yyflex_realloc(%#10lx,%8ld) total=%8ld return=%8lx\n",
                    (long)p,(long)n,(long)total_mem,(long)ptrs[i].p);
            dump_mem(stdout);
            return ptrs[i].p;
        }

    fprintf(stderr,"ERROR: yyflex_realloc could not locate pointer %#lx.\n",(long)p);
    dump_mem(stdout);
    exit(1);
}
