ValueToControls( double RawTime )
{

   RawTime = (double)((sampleCount)floor(RawTime * mSampleRate + 0.5)) / mSampleRate;
   double theValue = RawTime * mScalingFactor + .000001;
   int t_int;
   bool round = true;


   for(unsigned int i=0; i<mFields.GetCount(); i++) {
      if (mFields[i].frac)
         round = false;
   }
   if(round)
      t_int = int(theValue + 0.5);
   else
   {
      wxASSERT( mFields[mFields.GetCount()-1].frac );
      theValue += 0.5f / mFields[mFields.GetCount()-1].base;
      t_int = int(theValue);
   }
   double t_frac = (theValue - t_int);
   unsigned int i;
   int tenMins;
   int mins;
   int addMins;
   int secs;
   int frames;

   mValueString = mPrefix;

   if(mNtscDrop) {
      frames = (int)(theValue*30./1.001 + 0.5);
      tenMins = frames/17982;
      frames -= tenMins*17982;
      mins = tenMins * 10;
      if(frames >= 1800) {
         frames -= 1800;
         mins++;
         addMins = frames/1798;
         frames -= addMins*1798;
         mins += addMins;
         secs = frames/30;
         frames -= secs*30;
         frames += 2;
         if( frames >= 30 ) {
            secs++;
            frames -= 30;
         }
      }
      else {
         secs = frames/30;
         frames -= secs*30;
      }
      t_int = mins * 60 + secs;
      t_frac = frames / 30.;
   }

   for(i=0; i<mFields.GetCount(); i++) {
      int value;

      if (mFields[i].frac) {


         value = (int)(t_frac * mFields[i].base);


      }
      else {
         value = (t_int / mFields[i].base);
         if (mFields[i].range > 0)
            value = value % mFields[i].range;
      }

      wxString field = wxString::Format(mFields[i].formatStr, value);
      mValueString += field;
      mValueString += mFields[i].label;
   }

}
