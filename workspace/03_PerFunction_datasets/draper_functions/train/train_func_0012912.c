amsReadSuper(struct cpmSuperBlock *d, const char *format)
{
  unsigned char boot_sector[512], *boot_spec;
  const char *err;

  Device_setGeometry(&d->dev,512,9,40);
  if ((err=Device_readSector(&d->dev, 0, 0, (char *)boot_sector)))
  {
    fprintf(stderr,"%s: Failed to read Amstrad superblock (%s)\n",cmd,err);
    exit(1);
  }
  boot_spec=(boot_sector[0] == 0 || boot_sector[0] == 3)?boot_sector:(unsigned char*)0;


  if
  (
    (boot_sector[0] == 0xE9 || boot_sector[0] == 0xEB)
    && !memcmp(boot_sector + 0x2B, "CP/M", 4)
    && !memcmp(boot_sector + 0x33, "DSK",  3)
    && !memcmp(boot_sector + 0x7C, "CP/M", 4)
  ) boot_spec = boot_sector + 128;
  if (boot_spec==(unsigned char*)0)
  {
    fprintf(stderr,"%s: Amstrad superblock not present\n",cmd);
    exit(1);
  }


  d->type = CPMFS_DR3;
  d->secLength = 128 << boot_spec[4];
  d->tracks    = boot_spec[2];
  if (boot_spec[1] & 3) d->tracks *= 2;
  d->sectrk    = boot_spec[3];
  d->blksiz    = 128 << boot_spec[6];
  d->maxdir    = (d->blksiz / 32) * boot_spec[7];
  d->skew      = 1;
  d->skewtab   = (int*)0;
  d->boottrk   = boot_spec[5];
  d->size      = (d->secLength*d->sectrk*(d->tracks-d->boottrk))/d->blksiz;
  d->extents   = ((d->size>=256 ? 8 : 16)*d->blksiz)/16384;

  return 0;
}
