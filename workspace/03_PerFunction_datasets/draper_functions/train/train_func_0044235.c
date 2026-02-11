Predict(OBBase* pOb, string* param=NULL)
  {
    OBMol* pmol = dynamic_cast<OBMol*> (pOb);
    if(!pmol)
      return 0;

    OBSmartsPattern sp;
    sp.Init(_smarts);
    sp.Match(*pmol);
      return sp.GetUMapList().size();
  }
