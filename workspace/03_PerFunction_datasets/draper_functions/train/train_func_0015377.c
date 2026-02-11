Clear(void)
{
  if(META_DEBUG) METAIO_STREAM::cout << "MetaArrow: Clear" << METAIO_STREAM::endl;
  MetaObject::Clear();
  M_Length = 1;


  memset(M_Direction, 0, 10*sizeof(double));
  M_Direction[0] = 1.0;
}
