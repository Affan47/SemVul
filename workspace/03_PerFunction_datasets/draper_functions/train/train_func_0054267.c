read_file(File* filePtr)
{
	if (!read_with_record_size(filePtr, this, &visit_region_array<FileReaderVisitor>,
										REGION_ARRAY_RECORD_SIZE))
		return 0;

   if( region_info_count > 0 )
      region_info_array = (RegionInfo *) mem_add(sizeof(RegionInfo)*region_info_count);
   else
      region_info_array = NULL;

   if( !filePtr->file_read( region_info_array, sizeof(RegionInfo)*region_info_count))
      return 0;


	region_stat_count = filePtr->file_get_short();

	region_stat_array = (RegionStat*) mem_add( region_stat_count * sizeof(RegionStat) );

	if( !filePtr->file_read( region_stat_array, sizeof(RegionStat)*region_stat_count ) )
		return 0;


	int connectBit = (region_info_count -1) * (region_info_count) /2;
	int connectByte = (connectBit +7) /8;

	if( connectByte > 0)
	{
		connect_bits = (unsigned char *)mem_add(connectByte);
		if( !filePtr->file_read(connect_bits, connectByte) )
			return 0;
	}
	else
	{
		connect_bits = NULL;
	}

	return 1;
}
