Call0ArgsInNewReader(Obj f)

{


  Obj                 stackNams;
  UInt                countNams;
  UInt                readTop;
  UInt                readTilde;
  UInt                currLHSGVar;
  UInt                userHasQuit;
  syJmp_buf             readJmpError;
  UInt                intrCoding;
  UInt                intrIgnoring;
  UInt                nrError;
  Obj result;


  stackNams   = StackNams;
  countNams   = CountNams;
  readTop     = ReadTop;
  readTilde   = ReadTilde;
  currLHSGVar = CurrLHSGVar;
  userHasQuit = UserHasQuit;
  intrCoding = IntrCoding;
  intrIgnoring = IntrIgnoring;
  nrError = NrError;
  memcpy( readJmpError, ReadJmpError, sizeof(syJmp_buf) );


  StackNams   = NEW_PLIST( T_PLIST, 16 );
  CountNams   = 0;
  ReadTop     = 0;
  ReadTilde   = 0;
  CurrLHSGVar = 0;
  UserHasQuit = 0;
  IntrCoding = 0;
  IntrIgnoring = 0;
  NrError = 0;
  IntrBegin( BottomLVars );

  if (!READ_ERROR()) {
    result = CALL_0ARGS(f);
    PushVoidObj();

    IntrEnd( 0UL );
  } else {
    result = (Obj) 0L;
    IntrEnd( 1UL );
    ClearError();
  }


  memcpy( ReadJmpError, readJmpError, sizeof(syJmp_buf) );
  UserHasQuit = userHasQuit;
  StackNams   = stackNams;
  CountNams   = countNams;
  ReadTop     = readTop;
  ReadTilde   = readTilde;
  CurrLHSGVar = currLHSGVar;
  IntrCoding = intrCoding;
  IntrIgnoring = intrIgnoring;
  NrError = nrError;
  return result;
}
