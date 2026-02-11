gainCallback(void *data, t_symbol*s, int argc, t_atom*argv)
{
  if (argc<1)return;
  float X, Y;
  if(argc>1){
    X=atom_getfloat(argv);
    Y=atom_getfloat(argv+1);
  } else {
    Y=atom_getfloat(argv);
    X=1.0-Y;
  }
  GetMyClass(data)->gainMess(X, Y);
}
