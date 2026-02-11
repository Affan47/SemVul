vas_find_end_v1(void)
{
	struct map_hdr_v1 *hdr;
	u_long end;

	end = vas_map_base_v1->end_va;
	for(hdr = vas_map_base_v1; hdr; hdr = hdr->next)
		if(hdr->end_va > end)
			end = hdr->end_va;

	return end;
}
