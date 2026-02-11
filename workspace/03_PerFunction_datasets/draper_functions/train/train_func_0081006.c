cmdloop(void)
{
	Cmd *cmdp;
	File *ocurfile;
	int loaded;

	for(;;){
		if(!downloaded && curfile && curfile->unread)
			load(curfile);
		if((cmdp = parsecmd(0))==0){
			if(downloaded){
				rescue();
				exits("eof");
			}
			break;
		}
		ocurfile = curfile;
		loaded = curfile && !curfile->unread;
		if(cmdexec(curfile, cmdp) == 0)
			break;
		freecmd();
		cmdupdate();
		update();
		if(downloaded && curfile &&
		    (ocurfile!=curfile || (!loaded && !curfile->unread)))
			outTs(Hcurrent, curfile->tag);

		if(downloaded && curfile && curfile->rasp == 0)
			terminp = termoutp;
	}
}
