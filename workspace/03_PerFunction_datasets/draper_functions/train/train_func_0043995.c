test_extend_verify_cmpd_vl(unsigned lineno, const hsize_t *offset,
    const void *_test_val, const void *_compare_val)
{
    const comp_vl_datatype   *test_val = (const comp_vl_datatype *)_test_val;
    const comp_vl_datatype   *compare_val = (const comp_vl_datatype *)_compare_val;


    if((test_val->x != compare_val->x) ||
            HDstrcmp(test_val->a, compare_val->a) ||
            HDstrcmp(test_val->b, compare_val->b) ||
            (test_val->y != compare_val->y)) {
        HDfprintf(stdout, "%u: Value read was not expected.\n", lineno);
        HDfprintf(stdout,"    Elmt = {%Hu, %Hu, %Hu, %Hu, %Hu}, read: {%d, '%s', '%s', %d} "
                "expected: {%d, '%s', '%s', %d}\n",
                offset[0], offset[1], offset[2], offset[3], offset[4],
                test_val->x, test_val->a, test_val->b, test_val->y,
                compare_val->x, compare_val->a, compare_val->b, compare_val->y);
        goto error;
    }

    return 0;

error:
    return -1;
}
