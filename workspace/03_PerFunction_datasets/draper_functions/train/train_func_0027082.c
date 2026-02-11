callback1(void* arg)
{
    static int count = 0;
    int rc;

    switch (count) {
    case 0:
        printf("007 enter callback1 (TEMP)\n");
        rc = cr_checkpoint(CR_CHECKPOINT_TEMP_FAILURE);
        if (rc >= 0) {
	    printf("XXX resuming unexpectedly in callback1\n");
	    exit(-1);
        } else if (rc != -CR_ETEMPFAIL) {
	    printf("XXX callback1: checkpoint TEMP cancellation failed: %d (%s)\n", rc, cr_strerror(-rc));
	    exit(-1);
        } else {
	    printf("008 checkpoint cancelled successfully with TEMP fail\n");
        }
	break;

    case 1:
        printf("013 enter callback1 (OMIT)\n");
        rc = cr_checkpoint(CR_CHECKPOINT_OMIT);
        if (rc >= 0) {
	    printf("XXX resuming unexpectedly in callback_TEMP (rc=%d)\n", rc);
	    exit(-1);
        } else if (rc != -CR_EOMITTED) {
	    printf("XXX callback1: checkpoint OMIT cancellation failed: %d (%s)\n", rc, cr_strerror(-rc));
	    exit(-1);
        } else {
	    printf("014 checkpoint cancelled successfully with OMIT\n");
        }
	break;

    case 2:
        printf("019 enter callback1 (TEMP_CODE)\n");
        rc = cr_checkpoint(CR_CHECKPOINT_TEMP_FAILURE_CODE(911));
        if (rc >= 0) {
	    printf("XXX resuming unexpectedly in callback_TEMP_CODE (rc=%d)\n", rc);
	    exit(-1);
        } else if (rc != -911) {
	    printf("XXX callback1: checkpoint TEMP_CODE cancellation failed: %d (%s)\n", rc, cr_strerror(-rc));
	    exit(-1);
        } else {
	    printf("020 checkpoint cancelled successfully with TEMP_CODE\n");
        }
	break;

    default:
        (void)unlink(filename);
        printf("025 enter callback1 (PERM)\n");
        printf("026 DONE\n");
        (void)cr_checkpoint(CR_CHECKPOINT_PERM_FAILURE);
        printf("XXX cr_checkpoint(CR_CHECKPOINT_PERM_FAILURE) returned unexpectedly\n");
        exit(-1);
    }
    ++count;

    return 0;
}
