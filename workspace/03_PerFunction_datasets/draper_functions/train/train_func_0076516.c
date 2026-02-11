InitRows()
{
    PegRow* row;
    RowHint* hint;

    int xpos = 60;
    int ypos = mRowY0;
    int i;

    for (i = 0; i < mMaxRowCnt; ++i)
    {
        row = new PegRow();
        row->SetIx(i);
        row->setPos(QPoint(xpos, ypos + (mMaxRowCnt - (i + 1)) * 40));
        row->setZValue(LAYER_ROWS);
        row->SetActive(false);
        mScene->addItem(row);
        mPegRows[i] = row;
        connect(row, SIGNAL(RemovePegSignal(ColorPeg*)), mPegFactory, SLOT(RemovePegSlot(ColorPeg*)));
        connect(row, SIGNAL(RowSolutionSignal(int)), this, SLOT(RowSolutionSlot(int)));

        hint = new RowHint;
        hint->SetIx(i);
        hint->setPos(QPoint(4, ypos + (mMaxRowCnt - (i + 1)) * 40));
        hint->setZValue(LAYER_HINTS);
        hint->SetActive(false);
        mScene->addItem(hint);
        mHintBtns[i] = hint;
        connect(hint, SIGNAL(HintPressedSignal(int)), this, SLOT(HintPressedSlot(int)));
    }
}
