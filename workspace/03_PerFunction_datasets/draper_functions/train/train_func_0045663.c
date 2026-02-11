boolModel(MSBool &model_)
{
  if (_boolModel!=&model_)
   {
     _boolModel->removeReceiver(this);
     _boolModel=&model_;
     _boolModel->addReceiver(this);
   }
  newBoolModelNotify();
}
