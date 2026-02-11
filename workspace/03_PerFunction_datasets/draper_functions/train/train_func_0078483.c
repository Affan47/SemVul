get_key_name(int key_value)
{
	static char key_char[] = "'X'";
	const char *seq = NULL;
	int key;

	for (key = 0; key < ARRAY_SIZE(key_table); key++)
		if (key_table[key].value == key_value)
			seq = key_table[key].name;

	if (seq == NULL &&
	    key_value < 127 &&
	    isprint(key_value)) {
		key_char[1] = (char) key_value;
		seq = key_char;
	}

	return seq ? seq : "(no key)";
}
