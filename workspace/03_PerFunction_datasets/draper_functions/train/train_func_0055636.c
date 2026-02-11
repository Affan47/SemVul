cdb_find_file(UINT32 fad){


	int i;

	for(i = 0; i < CDB_FID_NUM; i++)
		if((CD_file[i].fad <= fad) &&
		   ((CD_file[i].fad + (CD_file[i].size + 2047) / 2048) > fad))
			return(i+2);

	return(0);
}
