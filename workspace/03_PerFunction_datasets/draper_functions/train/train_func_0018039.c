unuse_pool(struct atm_dev *dev,int pool)
{
	if (!(--ZATM_DEV(dev)->pool_info[pool].ref_count))
		drain_free(dev,pool);
}
