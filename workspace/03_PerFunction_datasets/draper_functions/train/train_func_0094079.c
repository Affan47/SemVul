Audio
        (unsigned r,unsigned b,unsigned c,
         const unsigned char*d, unsigned nsamples)
    {
        if(Terminate) return;
        if(!KnowAudio)
        {
            aud_rate = r;
            aud_chans = c;
            aud_bits = b;
            KnowAudio = true;
        }
        CheckFlushing();

        unsigned bytes = nsamples * aud_chans * (aud_bits / 8);

        unsigned wrote = 0;
        if(KnowVideo && AudioBuffer.empty())
        {

            wrote = NonblockWrite(audfp, d, bytes);

        }
        if(wrote < bytes)
        {
            unsigned remain = bytes-wrote;

            AudioBuffer.push_back(std::vector<unsigned char>(d+wrote, d+bytes));
            AudBufSize += remain;
        }
        CheckFlushing();
    }
