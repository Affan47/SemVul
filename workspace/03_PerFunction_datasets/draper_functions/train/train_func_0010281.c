IndexOUI() {
	char buf[1024];
	int line = 0;
	fpos_t prev_pos;
	short int m[3];

	if (mfile == NULL)
		return;

	_MSG("Indexing manufacturer db", MSGFLAG_INFO);

	fgetpos(mfile, &prev_pos);

	while (!feof(mfile)) {
		if (fgets(buf, 1024, mfile) == NULL || feof(mfile))
			break;

		if ((line % 50) == 0) {
			if (sscanf(buf, "%hx:%hx:%hx",
					   &(m[0]), &(m[1]), &(m[2])) == 3) {


				index_pos ip;
				uint32_t oui;

				oui = 0;
				oui |= (uint32_t) m[0] << 16;
				oui |= (uint32_t) m[1] << 8;
				oui |= (uint32_t) m[2];

				ip.oui = oui;
				ip.pos = prev_pos;

				index_vec.push_back(ip);
			} else {


				line--;
			}
		}

		fgetpos(mfile, &prev_pos);
		line++;
	}

	_MSG("Completed indexing manufacturer db, " + IntToString(line) + " lines " +
		 IntToString(index_vec.size()) + " indexes", MSGFLAG_INFO);
}
