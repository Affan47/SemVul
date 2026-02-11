setContentRange(FXint pxminArg, FXint pyminArg, FXint pxmaxArg, FXint pymaxArg){
  if(flags&PRINT_LANDSCAPE){
    pxmin=pyminArg;
    pymin=pxminArg;
    pxmax=pymaxArg;
    pymax=pxmaxArg;
    }
  else{
    pxmin=pxminArg;
    pymin=pyminArg;
    pxmax=pxmaxArg;
    pymax=pymaxArg;
    }
  return TRUE;
  }
