SetOutFormat(OBFormat* pOut)
  {
    pOutFormat=pOut;
    return pOut && !(pOutFormat->Flags() & NOTWRITABLE);
  }
