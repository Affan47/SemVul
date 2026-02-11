CL_ParseStartSoundPacket(sizebuf_t *msg)
{
    vec3_t  pos_v;
	float	*pos;
    int 	channel, ent;
    int 	sound_num, flags;
    float 	volume, attenuation, ofs;

	flags = MSG_ReadByte (msg);
	sound_num = MSG_ReadByte (msg);
	if( sound_num == -1 ) {
		Com_Error( ERR_DROP, "CL_ParseStartSoundPacket: read past end of message" );
	}

    if (flags & SND_VOLUME)
		volume = MSG_ReadByte(msg) * ONEDIV255;
	else
		volume = DEFAULT_SOUND_PACKET_VOLUME;

    if (flags & SND_ATTENUATION)
		attenuation = MSG_ReadByte(msg) * ONEDIV64;
	else
		attenuation = DEFAULT_SOUND_PACKET_ATTENUATION;

    if (flags & SND_OFFSET)
		ofs = MSG_ReadByte(msg) / 1000.0f;
	else
		ofs = 0;

	if (flags & SND_ENT)
	{
		channel = MSG_ReadShort(msg);
		ent = channel>>3;
		if ((unsigned)ent >= MAX_EDICTS)
			Com_Error (ERR_DROP,"CL_ParseStartSoundPacket: ent = %i", ent);

		channel &= 7;
	}
	else
	{
		ent = 0;
		channel = 0;
	}

	if (flags & SND_POS)
	{
		MSG_ReadPos (msg, pos_v);

		pos = pos_v;
	}
	else
		pos = NULL;

	if (!cl.sound_precache[sound_num])
		return;

	S_StartSound (pos, ent, channel, cl.sound_precache[sound_num], volume, attenuation, ofs);
}
