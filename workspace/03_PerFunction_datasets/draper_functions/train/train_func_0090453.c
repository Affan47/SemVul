getromdatabyid (int id)
{
	int i = 0;
	while (roms[i].name) {
		if (id == roms[i].id && roms[i].group == 0)
			return &roms[i];
		i++;
	}
	return 0;
}
