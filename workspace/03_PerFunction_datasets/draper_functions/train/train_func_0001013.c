rhash_transmit(unsigned msg_id, void* dst, rhash_uptr_t ldata, rhash_uptr_t rdata)
{
	rhash ctx = (rhash)dst;

	switch(msg_id) {
	case RMSG_GET_CONTEXT:
		{
			unsigned i;
			for(i = 0; i < ctx->hash_vector_size; i++) {
				struct rhash_hash_info* info = ctx->vector[i].hash_info;
				if(info->info.hash_id == (unsigned)ldata)
					return PVOID2UPTR(ctx->vector[i].context);
			}
			return (rhash_uptr_t)0;
		}

	case RMSG_CANCEL:

		atomic_compare_and_swap(&ctx->state, STATE_ACTIVE, STATE_STOPED);
		return 0;

	case RMSG_IS_CANCELED:
		return (ctx->state == STATE_STOPED);


#ifdef USE_OPENSSL
	case RMSG_SET_OPENSSL_MASK:
		rhash_openssl_hash_mask = (unsigned)ldata;
		break;
	case RMSG_GET_OPENSSL_MASK:
		return rhash_openssl_hash_mask;
#endif


	case RMSG_BT_ADD_FILE:
	case RMSG_BT_SET_OPTIONS:
	case RMSG_BT_SET_ANNOUNCE:
	case RMSG_BT_SET_PIECE_LENGTH:
	case RMSG_BT_SET_PROGRAM_NAME:
	case RMSG_BT_GET_TEXT:
		return process_bt_msg(msg_id, (torrent_ctx*)(((rhash_context*)dst)->bt_ctx), ldata, rdata);

	default:
		return RHASH_ERROR;
	}
	return 0;
}
