saveInputFileMetaInfo ( Char *srcName )
{
#  if BZ_UNIX
   IntNative retVal;

   retVal = MY_STAT( srcName, &fileMetaInfo );
   ERROR_IF_NOT_ZERO ( retVal );
#  endif
}
