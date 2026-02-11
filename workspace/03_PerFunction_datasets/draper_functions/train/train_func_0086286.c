dgap_verify_board(struct device *p)
{
	struct board_t *bd;

	if (!p)
		return NULL;

	bd = dev_get_drvdata(p);
	if (!bd || bd->magic != DGAP_BOARD_MAGIC || bd->state != BOARD_READY)
		return NULL;

	return bd;
}
