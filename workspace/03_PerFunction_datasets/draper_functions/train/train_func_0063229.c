getMachineInst( size_t Idx)
{
    if (Idx < mPhase1TEX_mi.size()) {
        return mPhase1TEX_mi[Idx];
    }
    else {
        Idx -= mPhase1TEX_mi.size();
        if (Idx < mPhase1ALU_mi.size()) {
            return mPhase1ALU_mi[Idx];
        }
        else {
            Idx -= mPhase1ALU_mi.size();
            if (Idx < mPhase2TEX_mi.size()) {
                return mPhase2TEX_mi[Idx];
            }
            else {
                Idx -= mPhase2TEX_mi.size();
                if (Idx < mPhase2ALU_mi.size()) {
                    return mPhase2ALU_mi[Idx];
                }

            }

        }

    }

    return 0;

}
