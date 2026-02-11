getCellUVString(BorderCellIndex idx) const
    {
        String ret = StringConverter::toString(mBorderUV[idx].u1) + " " +
                    StringConverter::toString(mBorderUV[idx].v1) + " " +
                    StringConverter::toString(mBorderUV[idx].u2) + " " +
                    StringConverter::toString(mBorderUV[idx].v2);
        return ret;
    }
