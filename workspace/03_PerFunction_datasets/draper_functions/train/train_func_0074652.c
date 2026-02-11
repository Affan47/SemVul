event_chord()
{
  if (cleanup) {
    if (inchord) {
      emit_string("]");
    } else {
      emit_string("[");
    };
  } else {
    emit_string("+");
  };
  inmusic = 1;
  inchord = 1 - inchord;
  chordcount = 0;
}
