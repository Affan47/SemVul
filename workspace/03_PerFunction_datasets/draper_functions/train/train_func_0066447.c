Do(OBBase* pOb, const char* OptionText, OpMap* pOptions, OBConversion* pConv)
{
  OBMol* pmol = dynamic_cast<OBMol*>(pOb);
  if(!pmol)
    return false;

  generateDiagram(pmol);
  pmol->SetDimension(2);

  return true;
}
