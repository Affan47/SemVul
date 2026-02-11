enclosure_init(void)
{
	int err;

	err = class_register(&enclosure_class);
	if (err)
		return err;

	return 0;
}
