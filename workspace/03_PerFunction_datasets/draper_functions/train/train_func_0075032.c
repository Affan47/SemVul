Populate()
{
   mSoloCodes.Add(wxT("Standard"));
   mSoloCodes.Add(wxT("Simple"));
   mSoloCodes.Add(wxT("None"));

   mSoloChoices.Add(_("Standard"));
   mSoloChoices.Add(_("Simple"));
   mSoloChoices.Add(_("None"));


   mViewCodes.Add(0);
   mViewCodes.Add(1);
   mViewCodes.Add(2);
   mViewCodes.Add(3);
   mViewCodes.Add(4);

   mViewChoices.Add(_("Waveform"));
   mViewChoices.Add(_("Waveform (dB)"));
   mViewChoices.Add(_("Spectrogram"));
   mViewChoices.Add(_("Spectrogram log(f)"));
   mViewChoices.Add(_("Pitch (EAC)"));


   ShuttleGui S(this, eIsCreatingFromPrefs);
   PopulateOrExchange(S);

}
