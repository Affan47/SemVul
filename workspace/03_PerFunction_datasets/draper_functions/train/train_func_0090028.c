ha_msg_addstruct_compress(struct ha_msg * msg, const char * name, const void * value)
{

	if (use_traditional_compression){
		return ha_msg_addraw(msg, name, strlen(name), value,
				     sizeof(struct ha_msg), FT_STRUCT, 0);
	}else{
		return ha_msg_addraw(msg, name, strlen(name), value,
				     sizeof(struct ha_msg), FT_UNCOMPRESS, 0);
	}
}
