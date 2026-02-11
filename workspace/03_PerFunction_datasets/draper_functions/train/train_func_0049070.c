findMFInfoStruct(A aobj)
{
  if(aplus_nl==aobj||0==MappedFileArray)R 0;
  DO(maxMFAindex,if(MappedFileArray[i].a==(I)aobj)R MappedFileArray+i);
  R 0;
}
