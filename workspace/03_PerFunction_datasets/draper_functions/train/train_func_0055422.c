load_internal_vars_from_rcfile_values(void)
{
  int i;

  sharedmem->do_mouse_input=!strcmp(cwinput,"mouse") || !strcmp(cwinput,"both");
  sharedmem->do_key_input=!strcmp(cwinput,"key") || !strcmp(cwinput,"both");
  sharedmem->do_snddev_output=!strcmp(cwoutput,"soundcard") ||
			!strcmp(cwoutput,"both");
  sharedmem->do_sounder_output=!strcmp(cwoutput,"sounder") ||
			!strcmp(cwoutput,"both");
  sharedmem->cwsound=!strcmp(cwsound,"beeps")?0:1;
  strncpy(sharedmem->snddev,snddev,FILENAME_MAX);
  sharedmem->snddev[FILENAME_MAX-1]=0;
  strncpy(sharedmem->serialdev,serialdev,FILENAME_MAX);
  sharedmem->serialdev[FILENAME_MAX-1]=0;
  sharedmem->doiambic=(keytype[0]=='i');
  sharedmem->iambicmode=(iambicmode[0]=='A'?0:iambicmode[0]=='B'?1:
			iambicmode[3]=='m'?2:3);
  sharedmem->do_midelementmodeB=midelementmodeB;
  sharedmem->do_ditmemory=ditmemory;
  sharedmem->do_dahmemory=dahmemory;
  sharedmem->do_autocharspacing=autocharspacing;
  sharedmem->do_autowordspacing=autowordspacing;
  sharedmem->invertpaddles=invertpaddles;
  sharedmem->dit_weight=ditweight;
  sharedmem->sidetone_mode=sidetone_mode;
  sharedmem->cwrxpitch=cwrxpitch;
  sharedmem->cwtxpitch=cwtxpitch;
  sharedmem->squelch=squelch;
  sharedmem->volume=volume;
  for(i=0;i<5;i++)
    sharedmem->cwchannel[i]=cwchannel[i];
  sharedmem->currcwchannel=currentcwchannel-1;
  sharedmem->wpm=wpm;
  sharedmem->debounce=debounce;
  sharedmem->recv_buffering=recv_buffering;
  strncpy(sharedmem->callsign,callsign,MAX_NICK_SIZE);
  sharedmem->callsign[MAX_NICK_SIZE-1]=0;
  strncpy(sharedmem->gridsquare,gridsquare,MAX_GRIDSQUARE_SIZE);
  sharedmem->gridsquare[MAX_GRIDSQUARE_SIZE-1]=0;
  sharedmem->send_callsign_with_cw=send_callsign_with_cw;
  sharedmem->send_gridsquare_with_cw=send_gridsquare_with_cw;
  sharedmem->reply_to_ctcp=reply_to_ctcp;
  sharedmem->give_callsign_in_ctcp_reply=give_callsign_in_ctcp_reply;
  sharedmem->give_gridsquare_in_ctcp_reply=give_gridsquare_in_ctcp_reply;
  sharedmem->give_cwchannel_in_ctcp_reply=give_cwchannel_in_ctcp_reply;
  sharedmem->simulate_qrn=simulate_qrn;
  sharedmem->qrnlevel=qrnlevel;
  sharedmem->simulate_signal_strength=simulate_signal_strength;
  sharedmem->simulate_sporadicE=simulate_sporadicE;
  sharedmem->default_signal_strength=default_signal_strength;
  for(sharedmem->cwcodeset=0;strcmp(cw_decoder_language,
	cwirc_cw_table[sharedmem->cwcodeset].lang);
	sharedmem->cwcodeset++);
}
