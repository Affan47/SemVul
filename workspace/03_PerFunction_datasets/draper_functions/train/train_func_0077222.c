Insert(double when, double value)
{
#if defined(__WXDEBUG__)

   if(when > mTrackLen + 0.0000001)
   {
      wxString msg;
      msg = wxString::Format(wxT("when %.20f mTrackLen %.20f diff %.20f"), when, mTrackLen, when-mTrackLen);
      wxASSERT_MSG(when <= (mTrackLen), msg);
   }
   if(when < 0)
   {
      wxString msg;
      msg = wxString::Format(wxT("when %.20f mTrackLen %.20f"), when, mTrackLen);
      wxASSERT_MSG(when >= 0, msg);
   }
#endif

   int len = mEnv.Count();

   if (len && when < 0.0)
      return 0;
   if ((len > 1) && when > mTrackLen)
      return len - 1;

   if (when < 0.0)
      when = 0.0;
   if ((len>1) && when > mTrackLen)
      when = mTrackLen;

   int i = 0;

   while (i < len && when > mEnv[i]->GetT())
      i++;

   if(i < len && when == mEnv[i]->GetT()) {


     mEnv[i]->SetVal(value);

   }
   else{


     EnvPoint *e = new EnvPoint(this, when, value);
     if (i < len) {
        mEnv.Insert(e, i);
     } else {
        mEnv.Add(e);
     }
   }
   return i;
}
