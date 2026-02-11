zend_mangle_property_name(char **dest, int *dest_length, const char *src1, int src1_length, const char *src2, int src2_length, int internal)
{
	char *prop_name;
	int prop_name_length;

	prop_name_length = 1 + src1_length + 1 + src2_length;
	prop_name = pemalloc(prop_name_length + 1, internal);
	prop_name[0] = '\0';
	memcpy(prop_name + 1, src1, src1_length+1);
	memcpy(prop_name + 1 + src1_length + 1, src2, src2_length+1);

	*dest = prop_name;
	*dest_length = prop_name_length;
}
