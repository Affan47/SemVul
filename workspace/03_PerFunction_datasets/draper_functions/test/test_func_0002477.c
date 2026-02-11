updatePseudoChildren()
{
    if (inUpdatePseudoChildren)
        return;
    inUpdatePseudoChildren = true;


    if (style()->styleType() == RenderStyle::BEFORE
     || style()->styleType() == RenderStyle::AFTER)
        return;

    updatePseudoChild(RenderStyle::BEFORE);
    updatePseudoChild(RenderStyle::AFTER);


    inUpdatePseudoChildren = false;
}
