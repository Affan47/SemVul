GetSeriesDescriptions(dicom_stl::vector<dicom_stl::string> &v)
{
  v.clear();

  DICOMAppHelperImplementation::SeriesUIDToInstanceUIDMapType::iterator miter;

  for (miter = this->Implementation->SeriesUIDToInstanceUIDMap.begin(); miter != this->Implementation->SeriesUIDToInstanceUIDMap.end();
       ++miter)
    {
    DICOMAppHelperImplementation::SeriesUIDToSeriesDescriptionMapType::iterator iiter = this->Implementation->SeriesUIDToSeriesDescriptionMap.find((*miter).first);
    if ( iiter != this->Implementation->SeriesUIDToSeriesDescriptionMap.end())
      {
      v.push_back( (*iiter).second );
      }
    else
      {
      dicom_stl::string value = "";
      v.push_back( value );
      }
   }
}
