event_info_key(key, value)
char* key;
char* value;

{
  int num;

  if (strcmp(key, "clef")==0) {
    event_clef(value);
  };
  if (strcmp(key, "octave")==0) {
    num = readsnumf(value);
    event_octave(num,0);
  };
}
