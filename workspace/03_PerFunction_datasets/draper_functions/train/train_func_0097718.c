operator=(const DcmDirectoryRecord& obj)
{
  if (this != &obj)
  {

    DcmItem::operator=(obj);

    recordsOriginFile = obj.recordsOriginFile;
    lowerLevelList = new DcmSequenceOfItems(*obj.lowerLevelList);
    DirRecordType = obj.DirRecordType;
    referencedMRDR = obj.referencedMRDR;
    numberOfReferences = obj.numberOfReferences;
    offsetInFile = obj.offsetInFile;
  }
  return *this;
}
