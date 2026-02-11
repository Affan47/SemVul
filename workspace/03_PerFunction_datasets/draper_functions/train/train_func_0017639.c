AddDerivationDescription()
{
  File &file = GetFile();
  DataSet &ds = file.GetDataSet();

  if( !this->Internals->DerivationDescription.empty() )
    {
    Attribute<0x0008,0x2111> at1;
    at1.SetValue( this->Internals->DerivationDescription.c_str() );
    ds.Replace( at1.GetAsDataElement() );
    }


  const Tag sisq(0x8,0x9215);
  SmartPointer<SequenceOfItems> sqi;
  sqi = new SequenceOfItems;
#ifdef ADD_DERIV
  if( ds.FindDataElement( sisq ) )
    sqi = ds.GetDataElement( sisq ).GetValueAsSQ();
#endif
  sqi->SetLengthToUndefined();

  Item item;
  item.SetVLToUndefined();


  DataSet &subds3 = item.GetNestedDataSet();

  unsigned int codevalue = this->Internals->DerivationCodeSequenceCodeValue;
  const CodeDefinition *cd = GetCodeDefinition( codevalue, ImageDerivation );
  if ( !cd )
    {
    return false;
    }

  std::ostringstream os;
  os << cd->CodeValue;

  Attribute<0x0008,0x0100> at1;
  at1.SetValue( os.str() );
  subds3.Replace( at1.GetAsDataElement() );
  Attribute<0x0008,0x0102> at2;
  at2.SetValue( cd->CodingSchemeDesignator );
  subds3.Replace( at2.GetAsDataElement() );
  Attribute<0x0008,0x0104> at3;
  at3.SetValue( cd->CodeMeaning );
  subds3.Replace( at3.GetAsDataElement() );

  sqi->AddItem( item );

  DataElement de( sisq );
  de.SetVR( VR::SQ );
  de.SetValue( *sqi );
  de.SetVLToUndefined();
  ds.Replace( de );

  return true;
}
