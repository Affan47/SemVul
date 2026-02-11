SetValueFieldLength( VL vl, bool readvalues )
{
  if( readvalues )
    ValueField->SetLength(vl);
  else
    ValueField->SetLengthOnly(vl);
}
