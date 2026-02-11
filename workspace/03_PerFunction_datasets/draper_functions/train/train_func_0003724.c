dirtyLinesFromChangedChild(RenderObject* child)
{
    if (!parent() || (selfNeedsLayout() && !isInlineFlow()) || isTable())
        return;


    if (!firstLineBox()) {


        if (isInline() && !parent()->selfNeedsLayout() && parent()->isInlineFlow())
            static_cast<RenderFlow*>(parent())->dirtyLinesFromChangedChild(this);
        return;
    }


    RootInlineBox* box = 0;
    RenderObject* curr = 0;
    for (curr = child->previousSibling(); curr; curr = curr->previousSibling()) {
        if (curr->isFloatingOrPositioned())
            continue;

        if (curr->isReplaced() && curr->isBox()) {
            InlineBox* placeHolderBox = static_cast<RenderBox*>(curr)->placeHolderBox();
            if (placeHolderBox)
                box = placeHolderBox->root();
        } else if (curr->isText()) {
            InlineTextBox* textBox = static_cast<RenderText*>(curr)->lastTextBox();
            if (textBox)
                box = textBox->root();
        } else if (curr->isInlineFlow()) {
            InlineRunBox* runBox = static_cast<RenderFlow*>(curr)->lastLineBox();
            if (runBox)
                box = runBox->root();
        }

        if (box)
            break;
    }
    if (!box)
        box = firstLineBox()->root();


    if (box) {
        RootInlineBox* adjacentBox;
        box->markDirty();


        adjacentBox = box->prevRootBox();
        if (adjacentBox)
            adjacentBox->markDirty();
        if (child->isBR() || (curr && curr->isBR())) {
            adjacentBox = box->nextRootBox();
            if (adjacentBox)
                adjacentBox->markDirty();
        }
    }
}
