crut_add_test(struct crut_operations *test_ops)
{
    int i;
    const char noname[] = "(unnamed)";


    test_ops->test_name[CRUT_TESTNAME_MAX] = '\0';

    if (!crut_initialized) {
	initialize_crut();
    }

    for (i=0; i<CRUT_MAX_TESTS; ++i) {
        if (!strncmp(crut_tests[i].test_name, test_ops->test_name, strlen(test_ops->test_name))) {
            fprintf(stderr, "Duplicate test (%s).\n", crut_tests[i].test_name);
	    exit(-1);
	} else if (crut_tests[i].test_name[0] == '\0') {
            memcpy(&crut_tests[i], test_ops, sizeof(*test_ops));
            if (crut_tests[i].test_name[0] == '\0') {
                strncpy(crut_tests[i].test_name, noname, sizeof(noname));
            }
	    goto out;
	}
    }

    switch (test_ops->test_scope) {
    case CR_SCOPE_PROC:
    case CR_SCOPE_TREE:
    case CR_SCOPE_PGRP:
	break;

    case CR_SCOPE_SESS:


    default:
        CRUT_FAIL("Invalid scope %d specified", test_ops->test_scope);
	exit(-1);
    }

out:
    return;
}
