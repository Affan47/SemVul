loadMoves() {
  char z[512];
  if (Loaded) return true;

  zifstream f(PGNSource);

  if (!f) {
    snprintf(z,512,_("can't load PGN move text from %s (error opening file)"),PGNSource);
    global.output->append(z,0xc0ff00);
    return false;
  }

  if (!f.seekg(SourceOffset)) {
    snprintf(z,512,_("can't seek to offset %lu of %s"),SourceOffset,PGNSource);
    global.output->append(z,0xc0ff00);
    f.close();
    return false;
  }

  if (!ParsePgnGame(f,PGNSource,false,-1,Variant,this)) {
    g_strlcpy(z,_("error parsing PGN data"),512);
    global.output->append(z,0xc0ff00);
    f.close();
    return false;
  }
  f.close();

  Loaded = true;
  return true;
}
