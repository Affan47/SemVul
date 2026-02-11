load(ifstream & f) {
        BitSequenceRRR * ret = NULL;
        try
        {
            ret = new BitSequenceRRR();
            uint type = loadValue<uint>(f);

            if(type!=RRR02_HDR) {
                abort();
            }
            ret->length = loadValue<size_t>(f);

            ret->ones = loadValue<size_t>(f);

            ret->C_len = loadValue<uint>(f);

            ret->C_field_bits = loadValue<uint>(f);

            ret->O_len = loadValue<uint>(f);

            ret->O_bits_len = loadValue<uint>(f);

            ret->sample_rate = loadValue<uint>(f);


            ret->C = loadValue<uint>(f,uint_len(ret->C_len,ret->C_field_bits));
            ret->O = loadValue<uint>(f,ret->O_len);
            ret->create_sampling(ret->sample_rate);
            return ret;
        }
        catch(exception e) {
            delete ret;
        }
        return NULL;
    }
