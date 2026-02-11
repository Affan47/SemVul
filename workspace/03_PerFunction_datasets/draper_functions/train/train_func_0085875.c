w1_therm_remove_slave(struct w1_slave *sl)
{
	int refcnt = atomic_sub_return(1, THERM_REFCNT(sl->family_data));
	while(refcnt) {
		msleep(1000);
		refcnt = atomic_read(THERM_REFCNT(sl->family_data));
	}
	kfree(sl->family_data);
	sl->family_data = NULL;
}
