ConvertLong(GUInt32* array, GInt32 length)
{
#ifdef CPL_LSB
   GUInt32* ptr;
   ptr = (GUInt32*)array;
   while(length--)
     CPL_SWAP32PTR(ptr++);
#endif
}
