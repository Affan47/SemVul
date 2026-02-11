powercap_init(void)
{
	int result = 0;

	result = seed_constraint_attributes();
	if (result)
		return result;

	result = class_register(&powercap_class);

	return result;
}
