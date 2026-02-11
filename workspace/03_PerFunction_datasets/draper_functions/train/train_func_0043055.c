instituteCompareP ( void *  instituteptr1, void * instituteptr2 )
{
  institute_t * i1, * i2;

  i1 = ( institute_t * ) instituteptr1;
  i2 = ( institute_t * ) instituteptr2;

  xassert(i1);
  xassert(i2);

  return instituteCompareKernel ( i1, i2 );
}
