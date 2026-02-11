freecmd(void)
{
	int i;

	while(cmdlist.nused > 0)
		free(cmdlist.voidpptr[--cmdlist.nused]);
	while(addrlist.nused > 0)
		free(addrlist.voidpptr[--addrlist.nused]);
	while(relist.nused > 0){
		i = --relist.nused;
		Strclose(relist.stringpptr[i]);
		free(relist.stringpptr[i]);
	}
	while(stringlist.nused>0){
		i = --stringlist.nused;
		Strclose(stringlist.stringpptr[i]);
		free(stringlist.stringpptr[i]);
	}
}
