faultPtr(wsdl__fault *fault)
{ faultRef = fault;
  if (!faultRef && vflag)
    cerr << "Warning: wsdl__ext_fault fault ref set to NULL" << endl;
}
