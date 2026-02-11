AddDICOMTagCallbackToAllTags(DICOMCallback* cb)
{
  DICOMParserMap::iterator miter;
  for (miter = Implementation->Map.begin();
       miter != Implementation->Map.end();
       miter++)
  {
  dicom_stl::vector<DICOMCallback*>* callbacks = (*miter).second.second;
  callbacks->push_back(cb);
  }
}
