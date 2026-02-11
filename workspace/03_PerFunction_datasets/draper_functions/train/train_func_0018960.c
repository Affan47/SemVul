TransferParameters(Shuttle & shuttle)
{
   shuttle.TransferDouble(wxT("RoomSize"), mParams.mRoomSize, 75);
   shuttle.TransferDouble(wxT("Delay"), mParams.mDelay, 10);
   shuttle.TransferDouble(wxT("Reverberance"), mParams.mReverberance, 50);
   shuttle.TransferDouble(wxT("HfDamping"), mParams.mHfDamping, 50);
   shuttle.TransferDouble(wxT("ToneLow"), mParams.mToneLow, 100);
   shuttle.TransferDouble(wxT("ToneHigh"), mParams.mToneHigh, 100);
   shuttle.TransferDouble(wxT("WetGain"), mParams.mWetGain, -1);
   shuttle.TransferDouble(wxT("DryGain"), mParams.mDryGain, -1);
   shuttle.TransferDouble(wxT("StereoWidth"), mParams.mStereoWidth, 100);

   shuttle.TransferBool(wxT("WetOnly"), mParams.mWetOnly, 0);

   return true;
}
