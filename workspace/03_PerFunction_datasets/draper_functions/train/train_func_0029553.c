cmd_delban()
{
	banlrec	*b;
	int num, tot;

	if(!cmdinfo.isparam)
	{
		say("Usage: delban <ban | #>");
		sayf(2,0,"Use this command to delete a ban from the banlist.  Specify the name of the ban or the ban number.");
		return;
	}

	if(isanumber(cmdinfo.tok1))
	{
		num = atoi(cmdinfo.tok1);
		tot = Banlist_orderbysettime();
		if(num < 1 && num > tot)
		{
			say("Invalid ban number %d.", num);
			return;
		}

		b = Banlist_banbyordernum(num);
	}
	else
		b = Banlist_ban(cmdinfo.tok1);

	if(b == NULL)
	{
		say("No such ban \"%s\" in the banlist.",cmdinfo.tok1);
		return;
	}

	say("Deleted \"%s\" from the banlist.",b->ban);
	Banlist_deleteban(b);

	Banlist->flags |= BANLIST_NEEDS_WRITE;
}
