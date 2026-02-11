Vindex_ref(int32 file_id,
           int32 sear_index)
{
    int32  find_ref = -1;
    int    index = 0;
    intn   found = FALSE;
    int32  ret_value = FAIL;

    while (!found && index != -1)
    {
	find_ref = Vgetid(file_id, find_ref);


	if (find_ref == FAIL)
	    index = -1;


	else if (index == sear_index)
	{

	    if (find_ref != -1)
	    {
		found = TRUE;
		ret_value = find_ref;
	    }
	    else
		printf("Warning>>> vgroup at index %d has an invalid ref# %d.\n"
			, sear_index, find_ref);
	}


	else
	    index++;
    }
    return ret_value;
}
