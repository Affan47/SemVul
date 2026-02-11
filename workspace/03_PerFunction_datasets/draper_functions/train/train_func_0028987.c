DCC_bootuser(dccrec *d, char *reason)
{
	context;
	if((d->flags & CLIENT_IRC_CHAT) || (d->flags & CLIENT_TELNET_CHAT))
	{
		if(!(d->flags & CLIENT_XFER))
		{
			DCC_write(d,"");
			if(reason != NULL)
				DCC_write(d,"*** %s",reason);
			DCC_write(d,"*** Bye!");
		}
		DCC_disconnect(d);
	}
}
