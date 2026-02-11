PrintDataSet(const DataSet &ds, const TransferSyntax & ts, std::ostream &os)
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict(); (void)d;

  DataSet::ConstIterator it = ds.Begin();
  UUIDGenerator UIDgen;

  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;

    const SequenceOfFragments *sqf = de.GetSequenceOfFragments();

    os << "<DicomAttribute  " ;
    VR refvr = PrintDataElement(os, dicts, ds, de, ts);

    if( refvr == VR::SQ  )
      {
      SmartPointer<SequenceOfItems> sqi2 = de.GetValueAsSQ();
      PrintSQ(sqi2, ts, os);
      }
    else if ( sqf )
      {


      unsigned long size = sqf->ComputeByteLength();
      char *bulkData = new char [size];
      if(sqf->GetBuffer(bulkData, size))
      	{
      	if(size)
      		{
      		const char *suid = UIDgen.Generate();
        	os << "<BulkData uuid = \""<<
        				 suid << "\" />\n";
        	HandleBulkData( suid, ts, bulkData, size);
      		}
      	}


      delete[] bulkData;
      }
    else
      {

      }
    os << "</DicomAttribute>\n";
    }
}
