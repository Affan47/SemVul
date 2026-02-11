decouple(void)
{
  if (model()!=0)
   {
     MSModel *m=model();
     _model=0;
     removeSender(m);
     if (internalModel()==MSTrue) delete m;
     internalModel(MSFalse);
     readOnlyModel(MSFalse);
   }
}
