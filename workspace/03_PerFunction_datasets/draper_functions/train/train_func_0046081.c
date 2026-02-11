flushUpTo(uint8 id)
{


    while(currentOp != lastOp && currentOp->first <= id)
    {
        currentOp->second->execute(mSceneManager, mRenderSystem);
        ++currentOp;
    }
}
