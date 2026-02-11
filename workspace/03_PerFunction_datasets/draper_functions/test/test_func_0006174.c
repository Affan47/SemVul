Check()


{
   REPORT
   if (skip!=0 || storage!=length)
      Throw(ProgramException("Illegal Conversion"));
}
