getTag_c()
{
	if(!tag){
		return 0;
	}
	if(!tag_c){
		const XMLCh *const tag_w=ParserHandler::getTagName(tag);
		tag_c=XMLString::transcode(tag_w);
	}
	return tag_c;
}
