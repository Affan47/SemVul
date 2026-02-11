multi_campaign_send_pool_status()
{
	ubyte data[MAX_PACKET_SIZE],val;
	int idx;
	int spool_size;
	int wpool_size;
	int packet_size = 0;


	BUILD_HEADER(CAMPAIGN_UPDATE);


	val = MC_CODE_POOL;
	ADD_DATA(val);


	if(!(Game_mode & GM_CAMPAIGN_MODE)){
		val = 0x0;
		ADD_DATA(val);
	}

	else {
		val = 0x1;
		ADD_DATA(val);


		spool_size = 0;
		for(idx=0;idx<Num_ship_classes;idx++){
			if(Campaign.ships_allowed[idx]){
				spool_size++;
			}
		}


		wpool_size = 0;
		for(idx=0;idx<Num_weapon_types;idx++){
			if(Campaign.weapons_allowed[idx]){
				wpool_size++;
			}
		}


		Assert((wpool_size + spool_size) < 480);


		val = (ubyte)spool_size;
		ADD_DATA(val);
		for(idx=0;idx<Num_ship_classes;idx++){
			if(Campaign.ships_allowed[idx]){
				val = (ubyte)idx;
				ADD_DATA(val);
			}
		}


		val = (ubyte)wpool_size;
		ADD_DATA(val);
		for(idx=0;idx<Num_weapon_types;idx++){
			if(Campaign.weapons_allowed[idx]){
				val = (ubyte)idx;
				ADD_DATA(val);
			}
		}
	}


	Assert(Net_player->flags & NETINFO_FLAG_AM_MASTER);
	multi_io_send_to_all_reliable(data, packet_size);


	multi_common_add_text(XSTR("Campaign ship/weapon pool\n",644),1);
}
