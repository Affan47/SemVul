nforce2_s4985_exit(void)
{
	if (s4985_adapter) {
		int i;

		for (i = 0; i < 5; i++)
			i2c_del_adapter(s4985_adapter+i);
		kfree(s4985_adapter);
		s4985_adapter = NULL;
	}
	kfree(s4985_algo);
	s4985_algo = NULL;


	if (i2c_add_adapter(nforce2_smbus))
		printk(KERN_ERR "i2c-nforce2-s4985: "
		       "Physical bus restoration failed\n");
}
