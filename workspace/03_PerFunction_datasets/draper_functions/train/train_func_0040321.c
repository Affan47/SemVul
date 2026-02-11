Init(){

static ClassDocumentation<PomeronPDF> documentation
    ("Implementation of the Diffractive PDFs");

 static Switch<PomeronPDF,int> interfacePDFFit
   ("PDFFit",
    "Switch between different PDF fits.",
    &PomeronPDF::PDFFit_, 0, true, false);
 static SwitchOption interfacePDFFit2007
   (interfacePDFFit,
    "2007",
    "Hera fit 2007",
    0);
 static SwitchOption interfacePDFFit2006A
   (interfacePDFFit,
    "2006A",
    "Hera fit A 2006",
    1);
 static SwitchOption interfacePDFFit2006B
   (interfacePDFFit,
    "2006B",
    "Hera fit B 2006",
    2);

  static Parameter<PomeronPDF,string> interfaceRootName
    ("RootName",
     "Root name for the input files",
     &PomeronPDF::rootName_, "",
     false, false);

  static Switch<PomeronPDF,int> interfaceBoundary
    ("Boundary",
     "Switch between different beheviours at out of PDF range.",
     &PomeronPDF::boundary_, 0, true, false);
  static SwitchOption interfaceBounderyExtrapolate
    (interfaceBoundary,
     "Extrapolate",
     "Extrapolate the PDF when it is out of range.",
     0);
  static SwitchOption interfaceBounderyFreeze
    (interfaceBoundary,
     "Freeze",
     "Freeze the value of PDF at the boundary.",
     1);
}
