load_sub_sprite_info()
{


	Database *dbSubSprite = game_set.open_db(SUB_SPRITE_DB);

	int subSpriteCount = dbSubSprite->rec_count();
	sub_sprite_info_array = (SubSpriteInfo*) mem_add( sizeof(SubSpriteInfo) * subSpriteCount );

	memset( sub_sprite_info_array, 0, sizeof(SubSpriteInfo) * subSpriteCount);

	for( int i=0 ; i<subSpriteCount; i++ )
	{
		SubSpriteRec *subSpriteRec = (SubSpriteRec *) dbSubSprite->read(i+1);
		SubSpriteInfo *subSpriteInfo = sub_sprite_info_array+i;

		subSpriteInfo->sprite_id = misc.atoi(subSpriteRec->sub_sprite_id, subSpriteRec->RECNO_LEN);
		err_when( subSpriteInfo->sprite_id > sprite_info_count );
		subSpriteInfo->sprite_info = sprite_info_array + subSpriteInfo->sprite_id -1;
		subSpriteInfo->offset_x = misc.atoi(subSpriteRec->offset_x, subSpriteRec->OFFSET_LEN);
		subSpriteInfo->offset_y = misc.atoi(subSpriteRec->offset_y, subSpriteRec->OFFSET_LEN);


		int subNo = misc.atoi(subSpriteRec->sub_no, subSpriteRec->SUB_NO_LEN);
		SpriteInfo *parentSprite = sprite_res[misc.atoi(subSpriteRec->sprite_id, subSpriteRec->RECNO_LEN)];

		if( subNo == 1)
			parentSprite->sub_sprite_info = subSpriteInfo;

		parentSprite->sub_sprite_count = subNo;
	}
}
