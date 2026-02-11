GenDtmfSamples(int16 *ToneBuf,int Samples)
{
   int Ret = 0;

   if(ToneGenSamples == 0) {
      if(bToneOn) {

         bToneOn = FALSE;

         ToneGenSamples = Pause == 0 ? DtmfEncodePause : Pause;
         ToneGenSamples *= 8000;
         ToneGenSamples /= 1000;
         Tone1Freq = 0;
         Tone2Freq = 0;
         DPRINT("Pausing for %d samples\n",ToneGenSamples);
      }
      else {

         int TimeMultiplier = 1;
         char Digit;
         int Index;
         for( ;  ; ) {
            if(*ToneChar != 0) {
               DPRINT("processing DTMF digit '%c'\n",*ToneChar);
            }
            else {
               DPRINT("processing end of DTMF string\n");
            }
            switch((Digit = tolower(*ToneChar++))) {
               case ' ':

                  continue;
                  break;

               case ':':

                  bGenDtmf = FALSE;
                  ToneGenSetup();
                  Index = -2;
                  break;

               case 0:
                  Index = -2;
                  bGenDtmf = FALSE;
                  break;

               case 'a':
               case 'b':
               case 'c':
               case 'd':
                  Index = 12 + Digit-'a';
                  break;

               case '0':
               case '1':
               case '2':
               case '3':
               case '4':
               case '5':
               case '6':
               case '7':
               case '8':
               case '9':
                  Index = Digit-'0';
                  break;

               case '*':
                  Index = 10;
                  break;

               case '#':
                  Index = 11;
                  break;

               case '+':
                  TimeMultiplier++;
                  continue;
                  break;

               default:
                  Index = -1;
                  break;
            }

            if(Index < 0) {
               if(Index == -1) {
                  LOG_ERROR(("%s: invalid DTMF digit \"%c\"\n",__FUNCTION__,Digit));
               }
               break;
            }

            bToneGenActive = TRUE;
            bToneOn = TRUE;


            ToneGenSamples = ToneDuration == 0 ? DtmfEncodeDuration : ToneDuration;
            ToneGenSamples *= TimeMultiplier * 8000;
            ToneGenSamples /= 1000;
            Tone1Freq = DtmfFreqLookup[Index].Row;
            Tone2Freq = DtmfFreqLookup[Index].Col;
            DeltaAngle1 = 2 * M_PI * Tone1Freq / 8000.0;
            DeltaAngle2 = 2 * M_PI * Tone2Freq / 8000.0;
            DeltaAngle1Delta = 0.0;
            break;
         }
      }
   }

   if(ToneGenSamples != 0) {
      Ret = GenSamples(ToneBuf,Samples);
   }

   return Ret;
}
