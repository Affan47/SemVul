PegReleasedSlot(ColorPeg* cp)
{
    if (cp == NULL || !cp) { return; }

    cp->setZValue(ColorCode::LAYER_PEGS);
    mWin->mScene->clearSelection();
    mWin->mScene->clearFocus();

    if (cp->GetSort() == 0)
    {
        emit(SnapPegSignal(cp));
    }
    else
    {
        int ystart = ColorCode::mRowY0 + (ColorCode::MAX_COLOR_CNT - ColorCode::mColorCnt) * 40;
        int ix1 = qRound((qRound(cp->pos().y()) - ystart + 18) / 40);
        ix1 = min(ColorCode::mColorCnt - 1, max(0, ix1));

        int ix0 = cp->GetPegType()->ix;
        if (ix0 != ix1)
        {
            ChangeColorOrder(cp->GetSort(), ix0, ix1);
        }
        RemovePegSlot(cp);
    }

    if (!mPegBtns[cp->GetPegType()->ix]->isEnabled())
    {
        mPegBtns[cp->GetPegType()->ix]->SetEnabled(true);
    }
}
