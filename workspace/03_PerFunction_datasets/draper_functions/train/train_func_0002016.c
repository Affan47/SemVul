addchordname(s, len, notes)

char *s;
int notes[];
int len;
{
  int i, j, done;

  if (strlen(s) > 7) {
    event_error("Chord name cannot exceed 7 characters");
    return;
  };
  if (len > 6) {
    event_error("Named chord cannot have more than 6 notes");
    return;
  };
  i = 0;
  done = 0;
  while ((i<chordsnamed) && (!done)) {
    if (strcmp(s, chordname[i]) == 0) {

      chordlen[i] = len;
      for (j=0; j<len; j++) {
        chordnotes[i][j] = notes[j];
      };
      done = 1;
    } else {
      i = i + 1;
    };
  };
  if (!done) {
    if (chordsnamed >= MAXCHORDNAMES-1) {
      event_error("Too many Guitar Chord Names used");
    } else {
      chordsnamed = chordsnamed + 1;
      strcpy(chordname[chordsnamed], s);
      chordlen[chordsnamed] = len;
      for (j=0; j<len; j++) {
        chordnotes[chordsnamed][j] = notes[j];
      };
    };
  };
}
