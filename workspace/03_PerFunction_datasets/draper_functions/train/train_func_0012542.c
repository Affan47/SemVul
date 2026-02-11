get_hmt_no_by_mtg_id_and_mt_no_from_block_list(int mtg_id, int mt_no, Block *head)
{
    Block *bpt;
    int hmt_no;

    for (bpt = head; bpt != NULL; bpt = bpt->next) {
	if(bpt->outer->hmdf != NULL
	   && bpt->outer->hmdf->mtg_id == mtg_id
	   && bpt->no == mt_no) {
	    return bpt->hmt_no;
	}
	if (bpt->inner != NULL) {
	    hmt_no =
		get_hmt_no_by_mtg_id_and_mt_no_from_block_list(mtg_id, mt_no, bpt->inner);
	    if (hmt_no > 0) {
		return hmt_no;
	    }
	}
    }
    return -1;
}
