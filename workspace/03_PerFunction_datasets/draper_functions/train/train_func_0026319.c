keyPressEvent(QKeyEvent *e)
{
    if (mCurRow == NULL || mGameState != STATE_RUNNING)
    {
        return;
    }

    switch (e->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (mGameMode == MODE_HVM)
            {
                int ix = mCurRow->GetIx();
                if (mHintBtns[ix]->mActive)
                {
                    std::vector<int> s = mCurRow->GetSolution();
                    if (s.size() == (unsigned) mPegCnt)
                    {
                        mHintBtns[ix]->SetActive(false);
                        HintPressedSlot(ix);
                    }
                }
            }
            else if (mGameMode == MODE_MVH)
            {
                if (mDoneBtn->isVisible() || mOkBtn->isVisible())
                {
                    DoneBtnPressSlot(mOkBtn);
                }
            }
        break;
    }
}
