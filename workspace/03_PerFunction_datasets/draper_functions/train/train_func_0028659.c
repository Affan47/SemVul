unmk_signature(unsigned char sig, unsigned char & base, saved_status & state, bool isolated)
    {
        if((sig & SAVED_FAKE_BIT) == 0 && !isolated)
            if(islower(sig))
                state = s_saved;
            else
                state = s_not_saved;
        else
            state = s_fake;

        base = tolower(sig & ~SAVED_FAKE_BIT);
    }
