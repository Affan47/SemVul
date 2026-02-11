GetContours(const dicom_stl::string &seriesUID,
                                 dicom_stl::vector<dicom_stl::vector<float> >& v)
{
  v.clear();

  DICOMAppHelperImplementation::SeriesUIDToContoursMapType::iterator iter = this->Implementation->SeriesUIDToContoursMap.find(seriesUID);

  if (iter == this->Implementation->SeriesUIDToContoursMap.end() )
    {
    return;
    }


  v = (*iter).second;
}
