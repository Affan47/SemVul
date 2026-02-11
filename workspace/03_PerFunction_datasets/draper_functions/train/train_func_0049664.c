dirtyInlineBoxes(bool fullLayout, bool)
{
    if (fullLayout)
        deleteInlineBoxes();
    else {
        for (InlineTextBox* box = firstTextBox(); box; box = box->nextTextBox())
            box->dirtyInlineBoxes();
    }
}
