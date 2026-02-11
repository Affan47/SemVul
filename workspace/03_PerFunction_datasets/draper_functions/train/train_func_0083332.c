mapif_parse_SaveStorage(int fd)
{
	int account_id=RFIFOL(fd,4);
	int len=RFIFOW(fd,2);

	if(sizeof(struct storage)!=len-8){
		printf("inter storage: data size error %lu %d\n",(unsigned long)sizeof(struct storage),len-8);
	} else {
		storagedb_save((struct storage *)RFIFOP(fd,8));
		mapif_save_storage_ack(fd,account_id);
	}
	return 0;
}
