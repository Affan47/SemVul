compile_vagconv_map (rRCOFile * rco, rRCOEntry * entry, void *arg)
{
  rRCOSoundEntry *rse = (rRCOSoundEntry *) entry->extra;

  if (entry->id != RCO_TABLE_SOUND || entry->type != 1 ||
      rse->format != RCO_SOUND_VAG)
    return;

  if (entry->srcFile[0] && entry->srcAddr == 0 &&
      entry->srcCompression == RCO_DATA_COMPRESSION_NONE &&
      !strcasecmp (entry->srcFile + strlen (entry->srcFile) - 4, ".wav")) {
    uint32_t len;
    int i;

    rse->channels = wav2vag (entry->srcFile, &len, &entry->srcBuffer, "");
    if (!rse->channels) {
      error ("WAV->VAG conversion failed for '%s'",
	  get_label_from_offset (rco->labels, entry->labelOffset));
      return;
    }
    entry->srcFile[0] = '\0';
    entry->srcLen = entry->srcLenUnpacked = len * rse->channels;
    entry->srcCompression = RCO_DATA_COMPRESSION_NONE;

    if (!rse->channelData)
      rse->channelData =
	  (uint32_t *) malloc (rse->channels * sizeof (uint32_t) * 2);
    for (i = 0; i < rse->channels; i++) {
      rse->channelData[i * 2] = len;
      rse->channelData[i * 2 + 1] = len * i;
    }
  }
}
