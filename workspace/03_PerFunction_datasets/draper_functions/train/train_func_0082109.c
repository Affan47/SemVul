nfs_pgio_data_destroy(struct nfs_pgio_header *hdr)
{
	if (hdr->args.context)
		put_nfs_open_context(hdr->args.context);
	if (hdr->page_array.pagevec != hdr->page_array.page_array)
		kfree(hdr->page_array.pagevec);
}
