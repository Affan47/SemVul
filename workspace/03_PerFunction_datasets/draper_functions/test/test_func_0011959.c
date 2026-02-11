fscheck_folder(btree* tree, hfsp_cat_folder* folder)
{
    UInt32  cnid    = tree->vol->vol.next_cnid;
    int	    result  = FSCK_NOERR;

    if (folder->flags & HFSP_FOLDER_RESERVED)
	printf("Warning unknown folder flags: %X\n", folder->flags);

    if (fsck_data.maxCnid < folder->id)
	fsck_data.maxCnid = folder->id;


    if (folder->id >= cnid)
    {
	printf("Folder id %ld >= volume next cnid %ld\n",
		    folder->id, cnid);
	result |= FSCK_FSCORR;
    }
    result |= fscheck_mactime(folder->create_date,	 "folder create_date");
    result |= fscheck_mactime(folder->content_mod_date,  "folder content_mod_date");
    result |= fscheck_mactime(folder->attribute_mod_date,"folder attribute_mod_date");
    result |= fscheck_mactime(folder->access_date,	 "folder access_date");
    result |= fscheck_mactime(folder->backup_date,	 "folder backup_date");


    return result;
}
