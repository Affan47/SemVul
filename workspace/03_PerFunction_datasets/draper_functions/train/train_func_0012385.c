pos()
{
  if(!io) { err = NotOpen; return 0; }
  return (long)io->tellg();
}
