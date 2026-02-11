PromptUser()
{
   AmplifyDialog dlog(this, mParent);
   dlog.peak = peak;
   if (peak > 0.0)
      dlog.ratio = 1.0 / peak;
   else
      dlog.ratio = 1.0;
   dlog.TransferDataToWindow();
   dlog.CenterOnParent();
   dlog.ShowModal();

  if (dlog.GetReturnCode() == wxID_CANCEL)
      return false;

   ratio = dlog.ratio;
   if (dlog.noclip && ratio*peak > 1.0)
      ratio = 1.0 / peak;

   return true;
}
