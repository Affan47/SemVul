ForceSnap(ColorPeg* cp, int posix)
{
    if (mColorPegs == NULL)
    {
        return;
    }

    if (posix > mPegCnt - 1)
    {
        return;
    }

    if (mIsActive)
    {
        if (mColorPegs[posix] != NULL)
        {
            emit RemovePegSignal(mColorPegs[posix]);
            mColorPegs[posix] = NULL;
        }
        mColorPegs[posix] = cp;
        cp->setSelected(false);
        cp->SetPegRow(this);
        cp->setPos(mapToParent(mXOffs + posix * 40 + 2, 2));

        CheckSolution();
    }
}
