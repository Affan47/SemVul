addChunk_tIME(ucvector* out, const LodePNG_Time* time)
{
  unsigned error = 0;
  unsigned char* data = (unsigned char*)malloc(7);
  if(!data) return 70;
  data[0] = (unsigned char)(time->year / 256);
  data[1] = (unsigned char)(time->year % 256);
  data[2] = time->month;
  data[3] = time->day;
  data[4] = time->hour;
  data[5] = time->minute;
  data[6] = time->second;
  error = addChunk(out, "tIME", data, 7);
  free(data);
  return error;
}
