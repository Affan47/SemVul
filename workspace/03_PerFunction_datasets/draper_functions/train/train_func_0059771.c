event_mrest(n,m)
int n, m;
{
  inmusic = 1;
  emit_string("Z");
  printlen(n,m);
  if (inchord) {
    event_error("Multiple bar rest not allowed in chord");
  };
  if (tuplenotes != 0) {
    event_error("Multiple bar rest not allowed in tuple");
  };
}
