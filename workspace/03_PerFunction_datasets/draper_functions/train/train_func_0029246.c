create(){
  FXTopWindow::create();
  if(getFirst() && getFirst()->shown()) show();
  }
