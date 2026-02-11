reader(char *filename, hid_t fapl)
{
    FILE	*script = NULL;
    hid_t	file = -1, mspace = -1, fspace = -1, d2 = -1;
    char	ln[128], *s;
    hsize_t	hs_offset[1];
    hsize_t	hs_size[1] = {WRT_SIZE};
    int		*buf = (int *)HDmalloc(sizeof(int) * WRT_SIZE);
    int		i, j, zero, wrong, nerrors = 0;


    script = HDfopen(DNAME, "r");


    if((file = H5Fopen(filename, H5F_ACC_RDONLY, fapl)) < 0) FAIL_STACK_ERROR


    if((d2 = H5Dopen2(file, "d2", H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    if((fspace = H5Dget_space(d2)) < 0) FAIL_STACK_ERROR


    if((mspace = H5Screate_simple(1, hs_size, hs_size)) < 0) FAIL_STACK_ERROR


    while(HDfgets(ln, (int)sizeof(ln), script)) {
        if('#' != ln[0])
            break;
        i = (int)HDstrtol(ln + 1, &s, 10);
        hs_offset[0] = HDstrtoll(s, NULL, 0);
        HDfprintf(stdout, "#%03d 0x%016Hx%47s", i, hs_offset[0], "");
        HDfflush(stdout);

        if(H5Sselect_hyperslab(fspace, H5S_SELECT_SET, hs_offset, NULL,
                hs_size, NULL) < 0) FAIL_STACK_ERROR
                if(H5Dread(d2, H5T_NATIVE_INT, mspace, fspace, H5P_DEFAULT, buf) < 0)
                    FAIL_STACK_ERROR


                    for(j = zero = wrong = 0; j < WRT_SIZE; j++) {
                        if(0 == buf[j])
                            zero++;
                        else if(buf[j] != i + 1)
                            wrong++;
                    }
        if(zero) {
            H5_FAILED();
            printf("    %d zero%s\n", zero, 1 == zero ? "" : "s");
        } else if(wrong) {
            SKIPPED();
            HDputs("    Possible overlap with another region.");
            nerrors++;
        } else {
            PASSED();
        }
    }

    if(H5Dclose(d2) < 0) FAIL_STACK_ERROR
            if(H5Sclose(mspace) < 0) FAIL_STACK_ERROR
            if(H5Sclose(fspace) < 0) FAIL_STACK_ERROR
            if(H5Fclose(file) < 0) FAIL_STACK_ERROR
            HDfree(buf);
    HDfclose(script);

    return nerrors;

error:
    H5E_BEGIN_TRY {
        H5Dclose(d2);
        H5Sclose(mspace);
        H5Sclose(fspace);
        H5Fclose(file);
    } H5E_END_TRY;
    if(buf)
        HDfree(buf);
    if(script)
        HDfclose(script);
    return 1;
}
