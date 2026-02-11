read_data_flow_from_block(mfgRec *mfg_data,
              mfgRec mfg_root_data[],
              Block  *current_mt_block,
              int mt_no)
{
    IntSet src;
    int i , j= 0, npre, *pre_array = NULL;

    copy_construct_IntSet(src,current_mt_block->pred);

    npre = number_IntSet(src);

    if (npre !=0 && (mfg_data->pred = (int *)calloc(npre,
                        sizeof(int))) == NULL) {
        fatal("No more room for pre in read mfg data!\n");
    }

    pre_array = mfg_data->pred;

    for (i = 1; i < (signed int)src[-2]; i++) {
	if (in_IntSet(src,i)) {
	    if (i < mt_no) {
		pre_array[j] = i;
		mfg_root_data[pre_array[j]-1].nsucd++;
		j++;
	    }
	}
    }

    mfg_data->npred = j;
}
