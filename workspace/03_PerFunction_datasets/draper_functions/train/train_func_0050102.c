determineStartPosition(bool fullLayout, BidiIterator& start, BidiState& bidi)
{
    RootInlineBox* curr = 0;
    RootInlineBox* last = 0;
    RenderObject* startObj = 0;
    int pos = 0;

    if (fullLayout) {


        if (firstRootBox()) {
            RenderArena* arena = renderArena();
            curr = firstRootBox();
            while (curr) {
                RootInlineBox* next = curr->nextRootBox();
                curr->deleteLine(arena);
                curr = next;
            }
            assert(!firstLineBox() && !lastLineBox());
        }
    } else {
        int cnt = 0;
        for (curr = firstRootBox(); curr && !curr->isDirty(); curr = curr->nextRootBox()) cnt++;
        if (curr) {


            if (RootInlineBox* prevRootBox = curr->prevRootBox()) {

                if (!prevRootBox->endsWithBreak() || (prevRootBox->lineBreakObj()->isText() && prevRootBox->lineBreakPos() >= static_cast<RenderText*>(prevRootBox->lineBreakObj())->stringLength()))


                    curr = prevRootBox;
            }
        } else {


            if (lastRootBox() && !lastRootBox()->endsWithBreak())
                curr = lastRootBox();
        }


        last = curr ? curr->prevRootBox() : lastRootBox();
    }

    m_firstLine = !last;
    previousLineBrokeAtBR = !last || last->endsWithBreak();
    if (last) {
        m_height = last->blockHeight();
        startObj = last->lineBreakObj();
        pos = last->lineBreakPos();
        bidi.status = last->lineBreakBidiStatus();
    } else {
        startObj = first(this, &bidi, false);
    }

    start = BidiIterator(this, startObj, pos);

    return curr;
}
