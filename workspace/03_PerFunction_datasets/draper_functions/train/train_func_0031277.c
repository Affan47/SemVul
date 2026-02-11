free_folder_entries(FLIST **flist)
{
    register int i;

    if(!(flist && *flist))
      return;

    i = (*flist)->used;
    while(i--){
	if((*flist)->folders[i]->nickname)
	  fs_give((void **) &(*flist)->folders[i]->nickname);

	fs_give((void **) &((*flist)->folders[i]));
    }

    fs_give((void **) &((*flist)->folders));
    fs_give((void **) flist);
}
