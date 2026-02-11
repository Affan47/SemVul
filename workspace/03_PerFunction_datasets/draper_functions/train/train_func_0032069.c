set_ide(unsigned int number, const char *dev_path, int cylinders, int heads, int spt, int byteswap, bool readonly, const char *model_name)
{

  if (cylinders == -1) {
    if ((cylinders = get_geometry(dev_path, geoCylinders)) == -1) {
      fprintf(stderr, "Disk %s has unknown geometry.\n", dev_path);
      exit(-1);
    }
  }

  if (heads == -1) {
    if ((heads = get_geometry(dev_path, geoHeads)) == -1) {
      fprintf(stderr, "Disk %s has unknown geometry.\n", dev_path);
      exit(-1);
    }
  }

  if (spt == -1) {
    if ((spt = get_geometry(dev_path, geoSpt)) == -1) {
      fprintf(stderr, "Disk %s has unknown geometry.\n", dev_path);
      exit(-1);
    }
  }

  if (byteswap == -1) {
    if ((byteswap = get_geometry(dev_path, geoByteswap)) == -1) {
      fprintf(stderr, "Disk %s has unknown geometry.\n", dev_path);
      exit(-1);
    }
  }

	bx_atadevice_options_t *disk;
	switch(number) {
		case 0: disk = diskc; break;
		case 1: disk = diskd; break;
		default: disk = NULL; break;
	}
  if (disk != NULL) {
    disk->present = strlen(dev_path) > 0;
    disk->isCDROM = false;
    disk->byteswap = byteswap;
    disk->readonly = readonly;
    disk->cylinders = cylinders;
    disk->heads = heads;
    disk->spt = spt;
    strcpy(disk->path, dev_path);
	safe_strncpy(disk->model, model_name, sizeof(disk->model));
  }

  if (cylinders && heads && spt) {
    D(bug("IDE%d CHS geometry: %d/%d/%d %d", number, cylinders, heads, spt, byteswap));
  }

}
