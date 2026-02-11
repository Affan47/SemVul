close()
{
  if (iN) {
    for (int k = iN; k < 3; ++k)
      iCh[k] = 0;
    uint w = base64word(iCh);
    char buf[5];
    base64encode(w, buf);
    for (int k = iN + 1; k < 4; ++k)
      buf[k] = '=';
    iStream.putCString(buf);
  }
  iStream.putCString("\n");
  iStream.close();
}
