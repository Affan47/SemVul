CloseWaveFile2()

{
   unsigned int pos;

   if((f_wave == NULL) || (f_wave == stdout))
      return;

   fflush(f_wave);
   pos = ftell(f_wave);

	fseek(f_wave,4,SEEK_SET);
	Write4Bytes(f_wave,pos - 8);

	fseek(f_wave,40,SEEK_SET);
	Write4Bytes(f_wave,pos - 44);


   fclose(f_wave);
   f_wave = NULL;

}
