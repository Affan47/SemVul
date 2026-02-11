GetMTime()
{
  unsigned long mTime=this->vtkObject::GetMTime();
  unsigned long time;

  for ( int i = 0; i < VTK_MAX_VRCOMP; i++ )
    {

    if (this->ColorChannels[i] == 1)
      {
      if (this->GrayTransferFunction[i])
        {

        time = this->GrayTransferFunctionMTime[i];
        mTime = (mTime > time ? mTime : time);


        time = this->GrayTransferFunction[i]->GetMTime();
        mTime = (mTime > time ? mTime : time);
        }
      }
    else if (this->ColorChannels[i] == 3)
      {
      if (this->RGBTransferFunction[i])
        {

        time = this->RGBTransferFunctionMTime[i];
        mTime = (mTime > time ? mTime : time);


        time = this->RGBTransferFunction[i]->GetMTime();
        mTime = (mTime > time ? mTime : time);
        }
      }


    if (this->ScalarOpacity[i])
      {

      time = this->ScalarOpacityMTime[i];
      mTime = (mTime > time ? mTime : time);


      time = this->ScalarOpacity[i]->GetMTime();
      mTime = (mTime > time ? mTime : time);
      }

    if (this->GradientOpacity[i])
      {

      time = this->GradientOpacityMTime[i];
      mTime = (mTime > time ? mTime : time);

      if (!this->DisableGradientOpacity[i])
        {

        time = this->GradientOpacity[i]->GetMTime();
        mTime = (mTime > time ? mTime : time);
        }
      }
    }

  return mTime;
}
