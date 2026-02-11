POSH_GetArchString( void )
{
   const char *err;
   const char *s = "OS:.............."POSH_OS_STRING"\n"
                   "CPU:............."POSH_CPU_STRING"\n"
                   "endian:.........."POSH_ENDIAN_STRING"\n"
                   "ptr size:........"POSH_POINTER_STRING"\n"
                   "64-bit ints......"POSH_64BIT_INTEGER_STRING"\n"
                   "floating point..."POSH_FLOAT_STRING"\n"
                   "compiler........."POSH_COMPILER_STRING"\n";


   err = s_testEndianess();

   if ( err != 0 )
   {
      return err;
   }


   err = s_testSerialization();

   if ( err != 0 )
   {
      return err;
   }

#if !defined POSH_NO_FLOAT

   err = s_testFloatingPoint();

   if ( err != 0 )
   {
      return err;
   }

#endif

   return s;
}
