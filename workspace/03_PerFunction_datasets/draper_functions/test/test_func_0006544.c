getSize() const
    {
        return sizeof(BitSequenceSDArray)+(ones?(sd.size + sd.sd0->size + sd.sd1->size):0);
    }
