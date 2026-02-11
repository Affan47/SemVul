mt9m111_resume(struct mt9m111 *mt9m111)
{
	int ret = mt9m111_enable(mt9m111);
	if (!ret)
		ret = mt9m111_reset(mt9m111);
	if (!ret)
		mt9m111_restore_state(mt9m111);

	return ret;
}
