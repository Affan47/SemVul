cmsStageFree(cmsStage* mpe)
{
    if (mpe ->FreePtr)
        mpe ->FreePtr(mpe);

    _cmsFree(mpe ->ContextID, mpe);
}
