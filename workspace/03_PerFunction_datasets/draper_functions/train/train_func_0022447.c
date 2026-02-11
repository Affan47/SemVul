GetReferencedInstanceUIDs(dicom_stl::vector<dicom_stl::string>& v)
{

  if (this->Implementation->SeriesUIDToInstanceUIDMap.size() > 0)
    {
    this->GetReferencedInstanceUIDs( (*this->Implementation->SeriesUIDToReferencedInstanceUIDMap.begin()).first, v );
    }
  else
    {
    v.clear();
    }
}
