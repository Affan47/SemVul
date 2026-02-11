GenerateInputRequestedRegion()
{

  if (this->GetNumberOfInputs() == 0)
    {
    return;
    }


  TemporalDataObject* tOutput = dynamic_cast<TemporalDataObject*>(this->GetOutput(0));
  TemporalDataObject* tInput = dynamic_cast<TemporalDataObject*>(this->GetInput(0));

  if (tOutput == ITK_NULLPTR)
    {
    itkExceptionMacro(<< "itk::TemporalProcessObject::GenerateInputRequestedRegion() "
                      << "cannot cast " << typeid(this->GetOutput(0)).name() << " to "
                      << typeid(TemporalDataObject*).name() );
    }
  else if (tInput == ITK_NULLPTR)
    {
    itkExceptionMacro(<< "itk::TemporalProcessObject::GenerateInputRequestedRegion() "
                      << "cannot cast " << typeid(this->GetInput(0)).name() << " to "
                      << typeid(TemporalDataObject*).name() );
    }
  else
    {
    this->GenerateInputRequestedTemporalRegion();
    }
}
