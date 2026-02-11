_dxf_initloader()
{
    if (!ltp) {
	ltp = (struct loadtable **)DXAllocateZero(DXProcessors(0) *
						  sizeof(struct loadtable *));
	if (!ltp)
	    return ERROR;

        ltl = (lock_type *)DXAllocate(sizeof(lock_type));
	if (!ltl)
	    return ERROR;

	if (DXcreate_lock(ltl, "loader") != OK)
	    return ERROR;

    }
    return OK;
}
