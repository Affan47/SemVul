findCodecInfo(fourcc_t fourcc,
		     avm::CodecInfo::Direction direction = avm::CodecInfo::Encode)
{
    uint_t i;
    const avm::vector<avm::CodecInfo>& list = video_codecs;

    for(i = 0; i < list.size(); i++){
	if(list[i].direction & direction){
	    if(list[i].fourcc == fourcc)
		return i;
	}
    }
    return avm::vector<const avm::CodecInfo>::invalid;
}
