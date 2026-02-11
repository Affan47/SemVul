Compare(OBBase* pOb, istream& optionText, bool noEval, std::string*)
{
  OBMol* pmol = dynamic_cast<OBMol*> (pOb);
  if(!pmol)
    return false;

  string title(pmol->GetTitle());
  return CompareStringWithFilter(optionText, title, noEval);
}
