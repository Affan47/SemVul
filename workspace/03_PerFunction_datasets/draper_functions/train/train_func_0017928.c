Layout()
{
   mMainSize = mMainPanel->GetBestSize();
   mExtraSize = mExtraPanel->GetBestSize();
   mButtonSize = wxSize(wxMax(mMainSize.x, mExtraSize.x),
                        kToggleButtonHeight);

   int left = 0;

   if (mGrabber) {
      mGrabberSize = mGrabber->GetMinSize();
      left += mGrabberSize.x;
   }
   else
      mGrabberSize = wxSize(0, 0);

   mMainPanel->SetSize(left, 0, mMainSize.x, mMainSize.y);
   mToggleButton->SetSize(left, mMainSize.y, mButtonSize.x, mButtonSize.y);
   mExtraPanel->SetSize(left, mMainSize.y + mButtonSize.y,
                        mExtraSize.x, mExtraSize.y);

   if (mGrabber)
      mGrabber->SetSize(0, 0, left, mMainSize.y + mButtonSize.y);


   return true;
}
