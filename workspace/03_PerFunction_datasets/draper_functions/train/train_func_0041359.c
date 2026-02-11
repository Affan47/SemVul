build(uint * bitseq, size_t len) const
    {
        return new BitSequenceRRR(bitseq,len,sample_rate);
    }
