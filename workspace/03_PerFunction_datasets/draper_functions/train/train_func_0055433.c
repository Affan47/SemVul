bc_testlist_generate(int codep, bytecode_info_t *retval,
				testlist_t *tl)
{
    int len_codep = codep;
    int testcount = 0;
    testlist_t *cur;

    codep++;


    if(!atleast(retval,codep+1))
	return -1;

    for(cur=tl; cur; cur=cur->next) {
	int oldcodep = codep;


	if(!atleast(retval,codep+1))
	    return -1;

	testcount++;
	codep = bc_test_generate(codep+1, retval, cur->t);

	retval->data[oldcodep].jump = codep;
    }

    retval->data[len_codep].listlen = testcount;

    return codep;
}
