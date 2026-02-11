itemdb_read_itemslottable(void)
{
	char *buf,*p;
	int s;

	buf = (char *)grfio_read("data\\itemslottable.txt");
	if(buf == NULL)
		return -1;
	s = grfio_size("data\\itemslottable.txt");

	buf[s] = 0;
	for(p=buf; p-buf<s; ) {
		int nameid,equip;
		sscanf(p,"%d#%d#",&nameid,&equip);
		itemdb_search(nameid)->equip = equip;
		p=strchr(p,'\n');
		if(!p) break;
		p++;
		p=strchr(p,'\n');
		if(!p) break;
		p++;
	}
	aFree(buf);

	return 0;
}
