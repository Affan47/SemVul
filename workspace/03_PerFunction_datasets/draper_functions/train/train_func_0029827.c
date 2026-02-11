delete_list_to_loop_info_list_alist(Loop_info_list_alist *infoList,
				    Block                *currBpt)
{
    int count = 0;

    if(infoList->loop_info_list_count <= 0){
	fatal("(mp_loop_info.c) : Unexpected number of list.\n");
    }else{
	(infoList->loop_info_list_count)--;

	count = infoList->loop_info_list_count;
	infoList->loop_info_list[count].loop_info = NULL;
	infoList->loop_info_list[count].entry = 0;
	infoList->loop_info_list[count].kind = KIND_UNDEC;

    }
}
