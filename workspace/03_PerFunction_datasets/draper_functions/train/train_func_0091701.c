nfs_get_readlink_reply ( struct nfs_readlink_reply *readlink_reply,
                             struct oncrpc_reply *reply ) {
	if ( ! readlink_reply || ! reply )
		return -EINVAL;

	readlink_reply->status = oncrpc_iob_get_int ( reply->data );
	switch ( readlink_reply->status )
	{
	case NFS3_OK:
		 break;
	case NFS3ERR_IO:
		return -EIO;
	case NFS3ERR_ACCES:
		return -EACCES;
	case NFS3ERR_INVAL:
		return -EINVAL;
	case NFS3ERR_NOTSUPP:
		return -ENOTSUP;
	case NFS3ERR_STALE:
		return -ESTALE;
	case NFS3ERR_BADHANDLE:
	case NFS3ERR_SERVERFAULT:
	default:
		return -EPROTO;
	}

	if ( oncrpc_iob_get_int ( reply->data ) == 1 )
		iob_pull ( reply->data, 5 * sizeof ( uint32_t ) +
		                        8 * sizeof ( uint64_t ) );

	readlink_reply->path_len = oncrpc_iob_get_int ( reply->data );
	readlink_reply->path     = reply->data->data;

	return 0;
}
