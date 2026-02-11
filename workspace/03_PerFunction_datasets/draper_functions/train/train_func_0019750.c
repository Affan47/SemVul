slic_init_driver(void)
{
	if (slic_first_init) {
		slic_first_init = 0;
		spin_lock_init(&slic_global.driver_lock);
	}
}
