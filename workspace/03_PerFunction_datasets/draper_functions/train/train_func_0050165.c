GetNumberOfIndexedInputs() const
{


  itkAssertInDebugAndIgnoreInReleaseMacro(  m_IndexedInputs.size() >= 1 );

  if (  m_IndexedInputs.size() > 1 )
    {
    return m_IndexedInputs.size();
    }
  return this->GetPrimaryInput() != NULL;
}
