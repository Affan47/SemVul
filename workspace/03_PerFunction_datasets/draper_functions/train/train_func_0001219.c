info_extract (struct EXTRACTOR_ExtractContext *ec,
	      uint32_t size)
{
  void *data;
  const struct infochunk *ichunk;
  char songs[32];

  if (size < 8)
    return 0;
  if (size >
      ec->read (ec->cls,
		&data,
		size))
    return 1;
  ichunk = data;

  if (0 != (ichunk->tvflags & DUAL_FLAG))
    {
      ADD ("PAL/NTSC", EXTRACTOR_METATYPE_BROADCAST_TELEVISION_SYSTEM);
    }
  else
    {
      if (0 != (ichunk->tvflags & PAL_FLAG))
        ADD ("PAL", EXTRACTOR_METATYPE_BROADCAST_TELEVISION_SYSTEM);
      else
        ADD ("NTSC", EXTRACTOR_METATYPE_BROADCAST_TELEVISION_SYSTEM);
    }

  if (0 != (ichunk->chipflags & VRCVI_FLAG))
    ADD ("VRCVI", EXTRACTOR_METATYPE_TARGET_ARCHITECTURE);
  if (0 != (ichunk->chipflags & VRCVII_FLAG))
    ADD ("VRCVII", EXTRACTOR_METATYPE_TARGET_ARCHITECTURE);
  if (0 != (ichunk->chipflags & FDS_FLAG))
    ADD ("FDS Sound", EXTRACTOR_METATYPE_TARGET_ARCHITECTURE);
  if (0 != (ichunk->chipflags & MMC5_FLAG))
    ADD ("MMC5 audio", EXTRACTOR_METATYPE_TARGET_ARCHITECTURE);
  if (0 != (ichunk->chipflags & NAMCO_FLAG))
    ADD ("Namco 106", EXTRACTOR_METATYPE_TARGET_ARCHITECTURE);
  if (0 != (ichunk->chipflags & SUNSOFT_FLAG))
    ADD ("Sunsoft FME-07", EXTRACTOR_METATYPE_TARGET_ARCHITECTURE);

  if (size < sizeof (struct infochunk))
    {
      ADD ("1", EXTRACTOR_METATYPE_SONG_COUNT);
      return 0;
    }
  snprintf (songs,
	    sizeof (songs),
	    "%d",
	    ichunk->songs);
  ADD (songs, EXTRACTOR_METATYPE_SONG_COUNT);
  snprintf (songs,
	    sizeof (songs),
	    "%d",
	    ichunk->firstsong);
  ADD (songs, EXTRACTOR_METATYPE_STARTING_SONG);
  return 0;
}
