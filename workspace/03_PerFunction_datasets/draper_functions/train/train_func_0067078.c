fgetstrz()
{
	FileOfs o = tell();

	char buf[64];
	int s, z = 0;
	bool found = false;
	while (!found) {
		s = read(buf, 64);
		for (int i=0; i < s; i++) {
			z++;
			if (buf[i] == 0) {
				found = true;
				break;
			}
		}
		if (s < 64) {
			break;
		}
	}
	if (s == 0) return ht_strdup("");

	char *str = ht_malloc(z);
	if (!str) throw std::bad_alloc();
	seek(o);
	readx(str, z);
	str[z-1] = 0;
	return str;
}
