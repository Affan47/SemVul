my_callback(void* arg)
{
    int rc;

    do_it("CHECKPOINT");
    rc = cr_checkpoint(0);
    if (rc > 0) {
	do_it("RESTART");
    } else if (!rc) {
	do_it("CONTINUE");
    }

    return 0;
}
