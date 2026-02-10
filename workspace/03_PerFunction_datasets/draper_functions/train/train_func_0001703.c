mdb_index_find_row(MdbHandle *mdb, MdbIndex *idx, MdbIndexChain *chain, guint32 pg, guint16 row)
{
	MdbIndexPage *ipg;
	int passed = 0;
	guint32 pg_row = (pg << 8) | (row & 0xff);
	guint32 datapg_row;

	ipg = mdb_index_read_bottom_pg(mdb, idx, chain);

	do {
		ipg->len = 0;


		if (!mdb_index_find_next_on_page(mdb, ipg)) {

			if (chain->cur_depth==1)
				return 0;


			while (chain->cur_depth>1) {
				chain->cur_depth--;
				if (!(ipg = mdb_find_next_leaf(mdb, idx, chain)))
					return 0;
				mdb_index_find_next_on_page(mdb, ipg);
			}
			if (chain->cur_depth==1)
				return 0;
		}

		datapg_row = mdb_get_int32_msb(mdb->pg_buf, ipg->offset + ipg->len - 4);
		if (pg_row == datapg_row) {
			passed = 1;
		}
		ipg->offset += ipg->len;
	} while (!passed);


	return 1;
}
