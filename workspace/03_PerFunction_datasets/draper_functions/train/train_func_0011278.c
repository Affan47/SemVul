mapif_load_quest(int fd,int account_id,int char_id)
{
	const struct quest *q = questdb_load(char_id);
	int p = 8;

	WFIFOW(fd,0)=0x3860;
	WFIFOL(fd,4)=account_id;

	if(q) {
		int i;

		for(i=0; i<q->count; i++,p+=27) {
			WFIFOL(fd,p)    = q->data[i].nameid;
			WFIFOB(fd,p+4)  = q->data[i].state;
			WFIFOL(fd,p+5)  = (unsigned int)q->data[i].limit;
			WFIFOW(fd,p+9)  = q->data[i].mob[0].id;
			WFIFOW(fd,p+11) = q->data[i].mob[0].max;
			WFIFOW(fd,p+13) = q->data[i].mob[0].cnt;
			WFIFOW(fd,p+15) = q->data[i].mob[1].id;
			WFIFOW(fd,p+17) = q->data[i].mob[1].max;
			WFIFOW(fd,p+19) = q->data[i].mob[1].cnt;
			WFIFOW(fd,p+21) = q->data[i].mob[2].id;
			WFIFOW(fd,p+23) = q->data[i].mob[2].max;
			WFIFOW(fd,p+25) = q->data[i].mob[2].cnt;
		}
	}

	WFIFOW(fd,2)=p;
	WFIFOSET(fd,p);

	return 0;
}
