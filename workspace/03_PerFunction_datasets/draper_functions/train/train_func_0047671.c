SV_RecordDemoMessage (void)
{
	int			e;
	edict_t		*ent;
	sizebuf_t	buf;
	byte		buf_data[32768];
	int			len;
	size_t		size;

	if (!svs.demofile)
		return;

	SZ_Init (&buf, buf_data, sizeof(buf_data));


	MSG_WriteByte (&buf, svc_frame);
	MSG_WriteLong (&buf, sv.framenum);

	MSG_WriteByte (&buf, svc_packetentities);

	e = 1;
	ent = EDICT_NUM(e);
	while (e < ge->num_edicts)
	{

		if (ent->inuse &&
			ent->s.number &&
			(ent->s.modelindex || ent->s.effects || ent->s.sound || ent->s.event) &&
			!(ent->svflags & SVF_NOCLIENT))
			MSG_WriteDeltaEntity (NULL, &ent->s, &buf, false, true);

		e++;
		ent = EDICT_NUM(e);
	}

	MSG_WriteShort (&buf, 0);


	SZ_Write (&buf, svs.demo_multicast.data, svs.demo_multicast.cursize);
	SZ_Clear (&svs.demo_multicast);


	len = LittleLong (buf.cursize);
	size = fwrite (&len, 4, 1, svs.demofile);
	size = fwrite (buf.data, buf.cursize, 1, svs.demofile);
}
