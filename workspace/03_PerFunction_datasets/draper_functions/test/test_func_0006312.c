matchedEndLine(const BidiIterator& start, const BidiStatus& status, BidiContext* context,
                                 const BidiIterator& endLineStart, const BidiStatus& endLineStatus, BidiContext* endLineContext,
                                 RootInlineBox*& endLine, int& endYPos)
{
    if (start == endLineStart)
        return status == endLineStatus && endLineContext && (*context == *endLineContext);
    else {


        static int numLines = 8;
        RootInlineBox* line = endLine;
        for (int i = 0; i < numLines && line; i++, line = line->nextRootBox()) {
            if (line->lineBreakObj() == start.obj && line->lineBreakPos() == start.pos) {

                if ((line->lineBreakBidiStatus() != status) || (line->lineBreakBidiContext() != context))
                    return false;
                RootInlineBox* result = line->nextRootBox();


                if (result)
                    endYPos = line->blockHeight();


                RootInlineBox* boxToDelete = endLine;
                RenderArena* arena = renderArena();
                while (boxToDelete && boxToDelete != result) {
                    RootInlineBox* next = boxToDelete->nextRootBox();
                    boxToDelete->deleteLine(arena);
                    boxToDelete = next;
                }

                endLine = result;
                return result;
            }
        }
    }
    return false;
}
