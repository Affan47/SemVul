SetTest(const char *testname, int action)
{
    int Loop;
    switch (action){
	case SKIPTEST:
	    for (Loop = 0; Loop < Index; Loop++)
		if (HDstrcmp(testname, Test[Loop].Name) == 0){
		    Test[Loop].SkipFlag = 1;
		    break;
		}
	    break;
	case BEGINTEST:
	    for (Loop = 0; Loop < Index; Loop++) {
		if (HDstrcmp(testname, Test[Loop].Name) != 0)
		    Test[Loop].SkipFlag = 1;
		else{

		    Test[Loop].SkipFlag = 0;
		    break;
		}
	    }
	    break;
	case ONLYTEST:
	    for (Loop = 0; Loop < Index; Loop++) {
		if (HDstrcmp(testname, Test[Loop].Name) != 0)
		    Test[Loop].SkipFlag = 1;
		else {

		    Test[Loop].SkipFlag = 0;
		    break;
		}
	    }

	    while (++Loop < Index)
		Test[Loop].SkipFlag = 1;
	    break;
	default:

	    printf("*** ERROR: Unknown action (%d) for SetTest\n", action);
	    break;
    }
}
