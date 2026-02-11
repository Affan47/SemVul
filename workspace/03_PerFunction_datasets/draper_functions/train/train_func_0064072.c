strProfile(unsigned short x)
{
	if (x == 0x0008)	return "CD-ROM";
	else if (x == 0x0009)	return "CD-R";
	else if (x == 0x000A)	return "CD-RW";
	else if (x == 0x0010)	return "DVD-ROM";
	else if (x == 0x0011)	return "DVD sequential recording";
	else if (x == 0x0012)	return "DVD-RAM";
	else if (x == 0x0013)	return "DVD-RW restricted overwrite";
	else if (x == 0x0014)	return "DVD-RW sequential recording";
	else if (x == 0x0015)	return "DVD-R DL sequential recording";
	else if (x == 0x0016)	return "DVD-R DL jump recording";
	else if (x == 0x0017)	return "DVD-RW dual layer";
	else if (x == 0x0018)	return "DVD-Download disc recording";
	else if (x == 0x001A)	return "DVD+RW";
	else if (x == 0x001B)	return "DVD+R";
	else if (x == 0x002A)	return "DVD+RW dual layer";
	else if (x == 0x002B)	return "DVD+R dual layer";
	return "?";
}
