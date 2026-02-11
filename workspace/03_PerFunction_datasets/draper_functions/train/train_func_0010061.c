formatString( const fDataType t )
{
  char* ret = (char*)malloc(100);

  switch(t.type)
    {
    case(INT):
      sprintf(ret,"%%%dd",t.sigDigits); break;
    case(STRING):
      sprintf(ret,"%%s"); break;
    case(FLOAT):
      sprintf(ret,"%%%d.%df",(t.sigDigits),(t.inSigDigits)); break;
    default:
      sprintf(ret,"unknown");
    }
  return ret;
}
