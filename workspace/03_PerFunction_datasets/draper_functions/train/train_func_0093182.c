Load( MemBuffer &file ) {
  type = file.Read8();
  for ( int i = 0; i < 4; ++i ) data[i] = file.Read16();
  return 0;
}
