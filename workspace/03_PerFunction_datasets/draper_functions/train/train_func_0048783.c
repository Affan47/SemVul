relativePositionOffset(int &tx, int &ty) const
{
    if (!style()->left().isAuto()) {
        if (!style()->right().isAuto() && containingBlock()->style()->direction() == RTL)
            tx -= style()->right().width(containingBlockWidth());
        else
            tx +=  style()->left().width(containingBlockWidth());
    } else if (!style()->right().isAuto())
        tx -= style()->right().width(containingBlockWidth());
    if(!style()->top().isAuto()) {
        if (style()->top().isPercent()) {
            float p = style()->top().percent();
            bool neg = p < 0.0;
            int ph = calcPercentageHeight(Length((neg?-p:p), Percent));
            if  (ph != -1)
                ty += neg?-ph:ph;
        } else {
            ty += style()->top().width(containingBlockHeight());
        }
    }
    else if(!style()->bottom().isAuto()) {
        if (style()->bottom().isPercent()) {
            float p = style()->bottom().percent();
            bool neg = p < 0.0;
            int ph = calcPercentageHeight(Length((neg?-p:p), Percent));
            if (ph != -1)
                ty -= neg?-ph:ph;
        } else {
            ty -= style()->bottom().width(containingBlockHeight());
        }
    }
}
