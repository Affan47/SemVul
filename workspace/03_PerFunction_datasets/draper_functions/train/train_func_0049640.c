open_raw_log()
{
    const char *tf = raw_log;
    if (stat(tf,&sbuf)) {
        SPRTF("%s: Failed to stat '%s'!\n", module, tf);
        return 1;
    }
    size_t size = sbuf.st_size;
    if (size <= MAX_RAW_LOG) {
        SPRTF("%s: Files '%s' too small! Only %u bytes!\n", module, tf, (int)size);
        return 1;

    }
    raw_log_size = size;
    raw_log_remaining = size;
    if (size > MAX_RAW_LOG) {
        size = MAX_RAW_LOG;
    }
    char *cp = (char *) malloc( size );
    if (!cp) {
        SPRTF("%s: memory allocation FAILED\n", module);
        return 1;
    }
    FILE *fp = fopen( tf, "rb" );
    if (!fp) {
        SPRTF("%s: Failed to open '%s'!\n", module, tf);
        free(cp);
        return 1;
    }
    size_t rd = fread(cp,1,size,fp);
    if (rd != size) {
        SPRTF("%s: Failed read of '%s'! Req %u, got %u?\n", module, tf, (int)size, (int)rd);
        fclose(fp);
        free(cp);
        return 1;
    }

    size_t i, j, bgn;
    for (i = 0; i < size; i++) {
        if ((cp[i+0] == 'S') && (cp[i+1] == 'F') &&
            (cp[i+2] == 'G') && (cp[i+3] == 'F')) {
            if (i) {

                bgn = i;
                j = 0;
                for ( ; i < size; i++) {
                    cp[j++] = cp[i];
                }
                rd = fread(&cp[j],1,bgn,fp);
                if (rd != bgn) {
                    SPRTF("%s: Failed read of '%s'! Req %u, got %u?\n", module, tf, (int)bgn, (int)rd);
                    fclose(fp);
                    free(cp);
                    return 1;
                }
            }

            for (i = 4; i < size; i++) {
                if ((cp[i+0] == 'S') && (cp[i+1] == 'F') &&
                    (cp[i+2] == 'G') && (cp[i+3] == 'F')) {

                    raw_log_fp = fp;
                    raw_log_buffer = cp;
                    raw_block_size = i;
                    raw_data_size = size;
                    raw_bgn_secs = get_seconds();
                    return 0;
                }
            }
        }
    }
    free(cp);
    if (fp)
        fclose(fp);
    SPRTF("%s: Failed find fisrt udp packet in '%s'!\n", module, tf);
    return 1;
}
