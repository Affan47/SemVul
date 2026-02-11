layout_update_len(struct nfsd4_layout_seg *lo, u64 end)
{
	if (end == NFS4_MAX_UINT64)
		lo->length = NFS4_MAX_UINT64;
	else
		lo->length = end - lo->offset;
}
