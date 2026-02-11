str2uuid(const char *uuidstr, char *uuid)
{
  int iret;
  unsigned int ui[16];

  if ( uuid == NULL ) return;
  if ( uuidstr == NULL ) return;

  uuid[0] = 0;

  if ( strlen(uuidstr) != 36 ) return;

  iret = sscanf(uuidstr, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		&ui[0], &ui[1], &ui[2], &ui[3], &ui[4], &ui[5], &ui[6], &ui[7],
		&ui[8], &ui[9], &ui[10], &ui[11], &ui[12], &ui[13], &ui[14], &ui[15]);

  if ( iret != 16 ) return;

  for ( int i = 0; i < 16; ++i ) uuid[i] = ui[i];

  uuid[16] = 0;
}
