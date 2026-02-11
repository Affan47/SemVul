multi_voice_server_process()
{
	int idx;


	for(idx=0;idx<MULTI_VOICE_MAX_STREAMS;idx++){
		switch(Multi_voice_stream[idx].token_status){

		case MULTI_VOICE_TOKEN_INDEX_FREE:
			break;


		case MULTI_VOICE_TOKEN_INDEX_RELEASED:

			if(Multi_voice_stream[idx].stream_last_heard == -1){
				Multi_voice_stream[idx].token_status = MULTI_VOICE_TOKEN_INDEX_FREE;

#ifdef MULTI_VOICE_VERBOSE
				nprintf(("Network","MULTI VOICE : freeing released token (no packets)\n"));
#endif
			}

			else {
				float t1,t2;
				t1 = f2fl(Multi_voice_stream[idx].stream_last_heard);
				t2 = f2fl(timer_get_fixed_seconds());
				if((t2 - t1) >= MULTI_VOICE_TOKEN_RELEASE_WAIT){
					Multi_voice_stream[idx].token_status = MULTI_VOICE_TOKEN_INDEX_FREE;

#ifdef MULTI_VOICE_VERBOSE
					nprintf(("Network","MULTI VOICE : freeing released token (time elapsed)\n"));
#endif
				}
			}
			break;


		default :

			if((Multi_voice_stream[idx].token_stamp != -1) && timestamp_elapsed(Multi_voice_stream[idx].token_stamp)){
				Assert(Multi_voice_stream[idx].token_status != MULTI_VOICE_TOKEN_INDEX_FREE);
				multi_voice_take_token(idx);
			}
			break;
		}
	}


	for(idx=0;idx<MAX_PLAYERS;idx++){
		if(MULTI_CONNECTED(Net_players[idx]) && (Net_players[idx].s_info.voice_token_timestamp != -1) && timestamp_elapsed(Net_players[idx].s_info.voice_token_timestamp)){

			Net_players[idx].s_info.voice_token_timestamp = -1;
		}
	}
}
