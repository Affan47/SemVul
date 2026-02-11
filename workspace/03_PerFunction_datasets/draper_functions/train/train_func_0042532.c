ll_handle_unlocking(struct afp_volume * volume,unsigned short forkid,
	uint64_t offset, uint64_t sizetorequest)
{
	uint64_t generated_offset;
	int rc;

	if (volume->extra_flags & VOLUME_EXTRA_FLAGS_NO_LOCKING)
		return 0;

	if (volume->server->using_version->av_number < 30)
		rc=afp_byterangelock(volume,ByteRangeLock_Unlock,
				forkid,offset, sizetorequest,
				(uint32_t *) &generated_offset);
	else
		rc=afp_byterangelockext(volume,ByteRangeLock_Unlock,
				forkid,offset, sizetorequest,&generated_offset);
	switch(rc) {
		case kFPNoErr:
			break;
		case kFPMiscErr:
		case kFPParamErr:
		case kFPRangeNotLocked:
		default:
			return -1;
	}
	return 0;
}
