build(const Array & seq) {
        uint cl = chunk_len;
        if(chunk_len==0) {
            uint s=0;
            for(size_t i=0;i<seq.getLength();i++)
                s = max(s,seq[i]);
            cl = 2*s;
        }
        cl = max(cl,(uint)64);
        return new SequenceGMR(seq, cl, bsb, sqb);
    }
