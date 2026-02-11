myaudiomixer(void *mydata, Uint8 *stream, int len)
{
   Uint8 *waveptr;
   int    waveleft;

   if(wave.sound != NULL && wave.repeat != 0)
   {

      waveptr  = wave.sound + wave.soundpos;
      waveleft = wave.soundlen - wave.soundpos;


      while( waveleft < len ) {
	 memcpy(stream, waveptr, waveleft);

	 stream += waveleft;
	 len -= waveleft;
	 waveptr = wave.sound;
	 waveleft = wave.soundlen;
	 wave.soundpos = 0;
	 if((wave.repeat -= 1) == 0) {
	    memset(stream, wave.silence, len);
	    break;
	 }
      }
      if(wave.repeat != 0) {


	 memcpy(stream, waveptr, len);

	 wave.soundpos += len;
      }
   }
   else {
       memset(stream, wave.silence, len);
   }
}
