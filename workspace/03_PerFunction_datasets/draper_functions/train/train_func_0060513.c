regTestCleanup(L_REGPARAMS  *rp)
{
char     result[512];
char    *results_file;
char    *text, *message;
l_int32  retval;
size_t   nbytes;

    PROCNAME("regTestCleanup");

    if (!rp)
        return ERROR_INT("rp not defined", procName, 1);

    fprintf(stderr, "Time: %7.3f sec\n", stopTimerNested(rp->tstart));
    fprintf(stderr, "################################################\n");


    if (!rp->fp) {
        FREE(rp->testname);
        FREE(rp->tempfile);
        FREE(rp);
        return 0;
    }


    fclose(rp->fp);
    text = (char *)l_binaryRead(rp->tempfile, &nbytes);
    FREE(rp->tempfile);
    if (!text) {
        rp->success = FALSE;
        FREE(rp);
        return ERROR_INT("text not returned", procName, 1);
    }


    if (rp->success)
        snprintf(result, sizeof(result), "SUCCESS: %s_reg\n", rp->testname);
    else
        snprintf(result, sizeof(result), "FAILURE: %s_reg\n", rp->testname);
    message = stringJoin(text, result);
    FREE(text);
    results_file = genPathname("/tmp", "reg_results.txt");
    fileAppendString(results_file, message);
    retval = (rp->success) ? 0 : 1;
    FREE(results_file);
    FREE(message);

    FREE(rp->testname);
    FREE(rp);
    return retval;
}
