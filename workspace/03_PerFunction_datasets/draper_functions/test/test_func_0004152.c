mapif_parse_GuildCastleDataLoad(int fd,int castle_id,int idx)
{
	struct guild_castle *gc;

	if(castle_id < 0 || castle_id >= MAX_GUILDCASTLE) {
		return mapif_guild_castle_dataload(castle_id,0,0);
	}
	gc = &castle_db[castle_id];

	switch(idx){
		case 1:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guild_id);             break;
		case 2:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->economy);              break;
		case 3:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->defense);              break;
		case 4:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->triggerE);             break;
		case 5:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->triggerD);             break;
		case 6:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->nextTime);             break;
		case 7:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->payTime);              break;
		case 8:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->createTime);           break;
		case 9:  return mapif_guild_castle_dataload(gc->castle_id,idx,gc->visibleC);             break;
		case 10: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[0].visible);  break;
		case 11: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[1].visible);  break;
		case 12: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[2].visible);  break;
		case 13: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[3].visible);  break;
		case 14: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[4].visible);  break;
		case 15: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[5].visible);  break;
		case 16: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[6].visible);  break;
		case 17: return mapif_guild_castle_dataload(gc->castle_id,idx,gc->guardian[7].visible);  break;
		default:
			printf("mapif_parse_GuildCastleDataLoad ERROR!! (Not found index=%d)\n", idx);
			break;
	}
	return 0;
}
