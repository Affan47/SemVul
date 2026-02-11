SaveDescriptorAsPatches( const libmv::vector<descriptor::Descriptor *> & desc)
{
  for (int i = 0; i < desc.size(); ++i) {
    const descriptor::VecfDescriptor * array =
      dynamic_cast<descriptor::VecfDescriptor *>( desc[i] );
    if(array) {
      const int size = sqrt((double)(array->coords.size()));
      Array3Df ima(size,size);
      for(int j=0; j< size; ++j)
      for(int i=0; i< size; ++i)
      {
        ima(j, i) = array->coords(j*size + i);
      }

      ostringstream os;
      os << "./Patch_000" << i << ".png";
      WritePng(ima, os.str().c_str());
    }
  }
}
