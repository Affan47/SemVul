UpdateUI()
{
   bool enable = mNormalizeCheckBox->GetValue();
   double v0, v1, v2;
   wxString val0 = mBassT->GetValue();
   val0.ToDouble(&v0);
   wxString val1 = mTrebleT->GetValue();
   val1.ToDouble(&v1);
   wxString val2 = mLevelT->GetValue();
   val2.ToDouble(&v2);


   mLevelT->Enable(enable);
   mLevelS->Enable(enable);

   wxButton *ok = (wxButton *) FindWindow(wxID_OK);
   wxButton *preview = (wxButton *) FindWindow(ID_EFFECT_PREVIEW);

   if (v0==0 && v1==0 && !enable)
   {

      ok->Enable(false);
      preview->Enable(true);
      mWarning->SetLabel(_("    No change to apply."));
   }
   else
   {
      if ((v2 > 0) && enable)
      {

         ok->Enable(false);
         preview->Enable(false);
         mWarning->SetLabel(_(":   Maximum 0 dB."));
      }
      else
      {

         ok->Enable(true);
         preview->Enable(true);
         mWarning->SetLabel(wxT(""));
      }
   }
}
