set_acc_block_flg(Block *block)
{
    Block *bpt;

    for (bpt = block; bpt != NULL; bpt = bpt->next) {
	if (bpt->inner != NULL) {
	    set_acc_block_flg(bpt->inner);
	}
	bpt->acc_block_flg = TRUE;
    }
}
