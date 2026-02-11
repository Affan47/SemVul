CalibrateNoise(WaveTrack & t, sampleCount start, sampleCount len){


   wxBusyCursor busy;


   double sumerg, sumerg2;
   double sumsc, sumsc2;
   double sumdc, sumdc2;
   double erg, sc, dc;


   double rate = t.GetRate();
   unsigned int WindowSizeInt = (unsigned int)(rate  * mWindowSize);


   erg = TestEnergy(t, start, WindowSizeInt);


   sc = TestSignChanges(t,start, WindowSizeInt);


   dc = TestDirectionChanges(t,start,WindowSizeInt);

   sumerg =0.0;
   sumerg2 = 0.0;
   sumsc =0.0;
   sumsc2 = 0.0;
   sumdc =0.0;
   sumdc2 =0.0;


   int samplesleft = len - WindowSizeInt;
   int i;
   int blocksize;
   int samples=0;

   for(i = start; samplesleft >=10 ; i += (WindowSizeInt -1), samplesleft -= (WindowSizeInt -1) )
      {


         samples++;
         if(samplesleft < (int)WindowSizeInt)
            {
               blocksize = samplesleft;
            }
         else
            {
               blocksize = WindowSizeInt;
            }

         erg = TestEnergy(t, i, blocksize);
         sumerg +=(double)erg;
         sumerg2 += pow((double)erg,2);

         sc = TestSignChanges(t,i, blocksize);
         sumsc += (double)sc;
         sumsc2 += pow((double)sc,2);


         dc = TestDirectionChanges(t,i,blocksize);
         sumdc += (double)dc;
         sumdc2 += pow((double)dc,2);
      }

   mEnergyMean = sumerg / samples;
   mEnergySD =  sqrt(sumerg2/samples - mEnergyMean*mEnergyMean);

   mSignChangesMean = sumsc / samples;
   mSignChangesSD = sqrt(sumsc2 / samples - mSignChangesMean * mSignChangesMean);

   mDirectionChangesMean = sumdc / samples;
   mDirectionChangesSD =sqrt(sumdc2 / samples - mDirectionChangesMean * mDirectionChangesMean) ;

   wxString text =   wxString::Format(_("Calibration Results\n"));

   text +=           wxString::Format(_("Energy                  -- mean: %1.4f  sd: (%1.4f)\n"),mEnergyMean,mEnergySD);
   text+=            wxString::Format(_("Sign Changes        -- mean: %1.4f  sd: (%1.4f)\n"),mSignChangesMean,mSignChangesSD);
   text+=            wxString::Format(_("Direction Changes  -- mean: %1.4f  sd: (%1.4f)\n"),mDirectionChangesMean,mDirectionChangesSD);
   wxMessageDialog  * stats =  new wxMessageDialog(NULL, text,
                                                  wxT("Calibration Complete"),
                                                  wxOK | wxICON_INFORMATION,
                                                  wxPoint(-1,-1));
   stats->ShowModal();
   delete stats;

   AdjustThreshold(mThresholdAdjustment);
}
