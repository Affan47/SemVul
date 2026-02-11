Get(samplePtr buffer, sampleFormat format,
                    int samplesToCopy)
{
   samplePtr dest;
   int block;
   int copied;
   int len = Len();

   if (samplesToCopy > len)
      samplesToCopy = len;

   dest = buffer;
   copied = 0;

   while(samplesToCopy) {
      block = samplesToCopy;
      if (block > mBufferSize - mStart)
         block = mBufferSize - mStart;

      CopySamples(mBuffer + mStart * SAMPLE_SIZE(mFormat), mFormat,
                  dest, format,
                  block);

      dest += block * SAMPLE_SIZE(mFormat);
      mStart = (mStart + block) % mBufferSize;
      samplesToCopy -= block;
      copied += block;
   }

   return copied;
}
