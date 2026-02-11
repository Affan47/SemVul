MSG_ReadShort (sizebuf_t *msg_read)
{
#if 0

	int	c;

	if (msg_read->readcount+2 > msg_read->cursize)
		c = -1;
	else
		c = (short)(msg_read->data[msg_read->readcount]
		+ (msg_read->data[msg_read->readcount+1]<<8));

	msg_read->readcount += 2;

	return c;
#else

	int c     = -1;
	int rc    = msg_read->readcount;
	short *pi = (short*)(&msg_read->data[ rc ]);

	rc += 2;
	if ( rc <= msg_read->cursize )
	{
		c = LittleShort( *pi );
		msg_read->readcount = rc;
	}

	return c;
#endif
}
