PutGLChecksum(void)
{
  uint32_g crc;
  lump_t *lump;
  char num_buf[64];

  Adler32_Begin(&crc);

  lump = FindLevelLump("VERTEXES");

  if (lump && lump->length > 0)
    Adler32_AddBlock(&crc, (uint8_g*) lump->data, lump->length);

  lump = FindLevelLump("LINEDEFS");

  if (lump && lump->length > 0)
    Adler32_AddBlock(&crc, (uint8_g*) lump->data, lump->length);

  Adler32_Finish(&crc);

  sprintf(num_buf, "0x%08x", crc);

  AddGLTextLine("CHECKSUM", num_buf);
}
