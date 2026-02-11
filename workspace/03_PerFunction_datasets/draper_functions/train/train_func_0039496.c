mode_changemode(chanrec *chan, int addmode, u_long type)
{
	if(addmode)
		chan->modes |= type;
	else
		chan->modes &= ~type;


}
