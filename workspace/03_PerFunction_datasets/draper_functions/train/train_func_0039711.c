allocate(size_t size)
{
  if (pdata){
    delete [] pdata;
    pdata=NULL;
  }

#ifdef __APPLE__
  try {
    data = pdata =  new unsigned char [size];
  } catch ( const std::bad_alloc & e) {
    error("out of memory!");
    data=pdata=NULL;
    datasize=0;
    return NULL;
  }

  datasize=size;
#else
  size_t array_size= size+(GEM_VECTORALIGNMENT/8-1);
  try {
    pdata = new unsigned char[array_size];
  } catch ( const std::bad_alloc & e) {
    error("out of memory!");
    data=pdata=NULL;
    datasize=0;
    return NULL;
  }

  size_t alignment = (reinterpret_cast<size_t>(pdata))&(GEM_VECTORALIGNMENT/8-1);
  size_t offset    = (alignment == 0?0:(GEM_VECTORALIGNMENT/8-alignment));
  data = pdata+offset;
  datasize=array_size-offset;
#endif
  notowned=false;

  return data;
}
