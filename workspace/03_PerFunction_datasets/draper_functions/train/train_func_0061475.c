refill_buffy(Remux *rem)
{
	pes_packet pes;
	int count = 0;
	int acount, vcount;
	ringbuffy *vbuf = &rem->vid_buffy;
	ringbuffy *abuf = &rem->aud_buffy;
	int fin = rem->fin;

	acount = abuf->size-ring_rest(abuf);
	vcount = vbuf->size-ring_rest(vbuf);


	while ( acount > MAX_PLENGTH && vcount > MAX_PLENGTH && count < 10){
		count++;
		init_pes(&pes);
		if (read_pes(fin,&pes) <= 0) return -1;
		switch(pes.stream_id){
		case AUDIO_STREAM_S ... AUDIO_STREAM_E:
			rem->apes++;
			if( rem->audio_info.layer < 0 &&
			    (pes.flags2 & PTS_DTS) )
				add_apts(rem, pes.pts);
			find_aframes( rem, pes.pes_pckt_data, pes.length);
			ring_write(abuf,(char *)pes.pes_pckt_data,pes.length);
			rem->awrite += pes.length;
			break;
		case VIDEO_STREAM_S ... VIDEO_STREAM_E:
			rem->vpes++;
			if( !rem->video_info.framerate &&
			    (pes.flags2 & PTS_DTS) )
				add_vpts(rem, pes.pts);

			find_vframes( rem, pes.pes_pckt_data, pes.length);

			ring_write(vbuf,(char *)pes.pes_pckt_data,pes.length);
			rem->vwrite += pes.length;
			break;
		}
		acount = abuf->size-ring_rest(abuf);
		vcount = vbuf->size-ring_rest(vbuf);
		kill_pes(&pes);
	}
	if (count < 10)	return 0;
	return 1;
}
