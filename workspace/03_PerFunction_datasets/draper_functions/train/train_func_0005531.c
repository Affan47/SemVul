bakeLodLevel(LodData* data, int lodIndex)
    {
        if(mFirstBufferPass){
            bakeFirstPass(data, lodIndex);
        } else {
            bakeSecondPass(data, lodIndex);
        }
        mFirstBufferPass = !mFirstBufferPass;
    }
