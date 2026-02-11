mdb_index_find_next_on_page(MdbHandle *mdb, MdbIndexPage *ipg)
{
	if (!ipg->pg) return 0;


	if (!ipg->idx_starts[0]){

		mdb_index_unpack_bitmap(mdb, ipg);
	}


	if (ipg->idx_starts[ipg->start_pos + 1]==0) return 0;
	ipg->len = ipg->idx_starts[ipg->start_pos+1] - ipg->idx_starts[ipg->start_pos];
	ipg->start_pos++;


	return ipg->len;
}
