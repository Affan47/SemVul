HTS_Engine_save_riff(HTS_Engine * engine, FILE * fp)
{
   size_t i;
   double x;
   short temp;

   HTS_GStreamSet *gss = &engine->gss;
   char data_01_04[] = { 'R', 'I', 'F', 'F' };
   int data_05_08 = HTS_GStreamSet_get_total_nsamples(gss) * sizeof(short) + 36;
   char data_09_12[] = { 'W', 'A', 'V', 'E' };
   char data_13_16[] = { 'f', 'm', 't', ' ' };
   int data_17_20 = 16;
   short data_21_22 = 1;
   short data_23_24 = 1;
   int data_25_28 = engine->condition.sampling_frequency;
   int data_29_32 = engine->condition.sampling_frequency * sizeof(short);
   short data_33_34 = sizeof(short);
   short data_35_36 = (short) (sizeof(short) * 8);
   char data_37_40[] = { 'd', 'a', 't', 'a' };
   int data_41_44 = HTS_GStreamSet_get_total_nsamples(gss) * sizeof(short);


   HTS_fwrite_little_endian(data_01_04, sizeof(char), 4, fp);
   HTS_fwrite_little_endian(&data_05_08, sizeof(int), 1, fp);
   HTS_fwrite_little_endian(data_09_12, sizeof(char), 4, fp);
   HTS_fwrite_little_endian(data_13_16, sizeof(char), 4, fp);
   HTS_fwrite_little_endian(&data_17_20, sizeof(int), 1, fp);
   HTS_fwrite_little_endian(&data_21_22, sizeof(short), 1, fp);
   HTS_fwrite_little_endian(&data_23_24, sizeof(short), 1, fp);
   HTS_fwrite_little_endian(&data_25_28, sizeof(int), 1, fp);
   HTS_fwrite_little_endian(&data_29_32, sizeof(int), 1, fp);
   HTS_fwrite_little_endian(&data_33_34, sizeof(short), 1, fp);
   HTS_fwrite_little_endian(&data_35_36, sizeof(short), 1, fp);
   HTS_fwrite_little_endian(data_37_40, sizeof(char), 4, fp);
   HTS_fwrite_little_endian(&data_41_44, sizeof(int), 1, fp);

   for (i = 0; i < HTS_GStreamSet_get_total_nsamples(gss); i++) {
      x = HTS_GStreamSet_get_speech(gss, i);
      if (x > 32767.0)
         temp = 32767;
      else if (x < -32768.0)
         temp = -32768;
      else
         temp = (short) x;
      HTS_fwrite_little_endian(&temp, sizeof(short), 1, fp);
   }
}
