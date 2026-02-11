TransferDataToWindow()
{
   mBassS->SetValue((double)bass);
   mTrebleS->SetValue((double)treble);
   mLevelS->SetValue((double)level);

   mBassT->SetValue(wxString::Format(wxT("%.1f"), (float)bass));
   mTrebleT->SetValue(wxString::Format(wxT("%.1f"), (float)treble));
   mLevelT->SetValue(wxString::Format(wxT("%.1f"), (float)level));

   mNormalizeCheckBox->SetValue(mbNormalize);
   UpdateUI();
   TransferDataFromWindow();

   return true;
}
