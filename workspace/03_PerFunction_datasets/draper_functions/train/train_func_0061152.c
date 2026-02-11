cmd_delnick()
{
	context;
	if(!cmdinfo.isparam)
	{
		say("Usage: delnick <nick>");
		sayf(2,0,"Use this command to delete a nick from your account.");
		return;
	}

	context;

	if(!User_isnick(cmdinfo.user,cmdinfo.tok1))
	{
		sayf(0,0,"Your account does not contain the nick \"%s\".  Doh!",cmdinfo.tok1);
		return;
	}

	context;

	if(isequal(cmdinfo.tok1,cmdinfo.user->acctname))
	{
		sayf(0,0,"You can't delete that nick!  One of your nicks MUST be your account name.  Sorry!");
		return;
	}

	context;

	if(isequal(cmdinfo.tok1,cmdinfo.from_n))
	{
		sayf(0,0,"You're deleting the nick you're currently using!  Ok... but you'll have to change to one of your other nicks in order to access your account after this.  Bye!");
		say("");
	}

	context;

	User_removenick(cmdinfo.user,cmdinfo.tok1);
	User_releaseaccounts(cmdinfo.user,cmdinfo.tok1);

	context;

	User_resetallpointers();

	say("The nick \"%s\" has been deleted from your account.",cmdinfo.tok1);
}
