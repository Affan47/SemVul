PromptUser()
{
   wxString fmt;

   if (mT1 > mT0) {

      mDuration = mT1 - mT0;
      fmt = _("hh:mm:ss + samples");
   } else {

      gPrefs->Read(wxT("/Effects/SilenceGen/Duration"), &mDuration, 30L);
      fmt = _("hh:mm:ss + milliseconds");
   }

   TimeDialog dlog(mParent, _("Silence Generator"), fmt, mProjectRate,
      mDuration );

   if (dlog.ShowModal() == wxID_CANCEL)
      return false;

   mDuration = dlog.GetTimeValue();


   if (mT1 == mT0)
   {
      gPrefs->Write(wxT("/Effects/SilenceGen/Duration"), mDuration);
      gPrefs->Flush();
   }

   return true;
}
