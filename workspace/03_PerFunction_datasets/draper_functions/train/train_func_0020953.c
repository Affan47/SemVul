biosdisk (int read, int drive, struct geometry *geometry,
	  int sector, int nsec, int segment)
{
  int err;

  if (geometry->flags & BIOSDISK_FLAG_LBA_EXTENSION)
    {
      struct disk_address_packet
      {
	unsigned char length;
	unsigned char reserved;
	unsigned short blocks;
	unsigned long buffer;
	unsigned long long block;
      } __attribute__ ((packed)) dap;


#ifdef NO_BUGGY_BIOS_IN_THE_WORLD
      if (sector >= geometry->total_sectors)
	return BIOSDISK_ERROR_GEOMETRY;
#endif


      dap.length = sizeof (dap);
      dap.block = sector;
      dap.blocks = nsec;
      dap.reserved = 0;


      dap.buffer = segment << 16;

      err = biosdisk_int13_extensions ((read + 0x42) << 8, drive, &dap);


#ifndef NO_INT13_FALLBACK
      if (err)
	{
	  if (geometry->flags & BIOSDISK_FLAG_CDROM)
	    return err;

	  geometry->flags &= ~BIOSDISK_FLAG_LBA_EXTENSION;
	  geometry->total_sectors = (geometry->cylinders
				     * geometry->heads
				     * geometry->sectors);
	  return biosdisk (read, drive, geometry, sector, nsec, segment);
	}
#endif

    }
  else
    {
      int cylinder_offset, head_offset, sector_offset;
      int head;


      sector_offset = sector % geometry->sectors + 1;
      head = sector / geometry->sectors;
      head_offset = head % geometry->heads;
      cylinder_offset = head / geometry->heads;

      if (cylinder_offset >= geometry->cylinders)
	return BIOSDISK_ERROR_GEOMETRY;

      err = biosdisk_standard (read + 0x02, drive,
			       cylinder_offset, head_offset, sector_offset,
			       nsec, segment);
    }

  return err;
}
