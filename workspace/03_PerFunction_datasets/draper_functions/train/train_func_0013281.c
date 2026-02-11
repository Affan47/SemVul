GetMolID()
  {
    stringstream molID;
    if(strlen(_pmol->GetTitle())==0)
      molID << "Mol #" << _pxmlConv->GetOutputIndex()+1;
    else
      molID << _pmol->GetTitle();

    string fn(_pxmlConv->GetInFilename());

    string::size_type pos = fn.rfind(getSeparator());
    if(pos!=string::npos)
      fn.erase(0,pos+1);
    molID << " (in " << fn << ')';
    return molID.str();
  }
