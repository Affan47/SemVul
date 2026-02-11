LOAD_BYTE_BUF( void )
{
  Int ret;
  ret = read(syBuf[LoadFile].fp, LoadBuffer, 100000);
  if (ret <= 0)
    {
      Pr(LoadByteErrorMessage, 0L, 0L );
      SyExit(2);
    }
  LBEnd = LoadBuffer + ret;
  LBPointer = LoadBuffer;
  return *LBPointer++;
}
