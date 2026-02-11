Read256(float *buffer,
                        sampleCount start, sampleCount len)
{
   wxASSERT(start >= 0);

   char *summary = new char[mSummaryInfo.totalSummaryBytes];
   this->ReadSummary(summary);

   if (start+len > mSummaryInfo.frames256)
      len = mSummaryInfo.frames256 - start;

   CopySamples(summary + mSummaryInfo.offset256 + (start * mSummaryInfo.bytesPerFrame),
               mSummaryInfo.format,
               (samplePtr)buffer, floatSample, len * mSummaryInfo.fields);

   if (mSummaryInfo.fields == 2) {

      int i;
      for(i=len-1; i>=0; i--) {
         buffer[3*i+2] = (fabs(buffer[2*i]) + fabs(buffer[2*i+1]))/4.0;
         buffer[3*i+1] = buffer[2*i+1];
         buffer[3*i] = buffer[2*i];
      }
   }

   delete[] summary;

   return true;
}
