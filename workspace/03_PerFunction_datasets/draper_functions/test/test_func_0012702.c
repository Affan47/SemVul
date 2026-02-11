ApplyColorCnt()
{
    int ccnt = mSettings->mColorCnt;
    ccnt = max(2, min(10, ccnt));

    if (ColorCode::mColorCnt == ccnt)
    {
        return;
    }

    ColorCode::mColorCnt = ccnt;

    int ystart = ColorCode::mRowY0 + (ColorCode::MAX_COLOR_CNT - ccnt) * 40;
    int ypos;
    int i;

    for (i = 0; i < ColorCode::MAX_COLOR_CNT; ++i)
    {
        ypos = ystart + i * 40 + 2;
        mBtnPos[i] = QPoint(XPOS_BTNS_COL, ypos);

        if (i < ColorCode::mColorCnt)
        {
            if (mPegBtns[i] == NULL)
            {
                mPegBtns[i] = CreatePeg(i);
            }
            mPegBtns[i]->setPos(mBtnPos[i]);
            mPegBtns[i]->setVisible(true);
        }
        else if (mPegBtns[i] != NULL)
        {
            mPegBtns[i]->setVisible(false);
        }
    }
}
