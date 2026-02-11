insertSpace(TextImpl *textNode, unsigned long offset)
{
    assert(textNode);

    DOMString text(textNode->data());


    int count = 0;
    for (unsigned int i = offset; i < text.length(); i++) {
        if (isWS(text[i]))
            count++;
        else
            break;
    }
    if (count > 0) {


        Position pos(textNode, offset);
        Position downstream = pos.equivalentDownstreamPosition();
        if (downstream.offset() < (long)text.length() && isWS(text[downstream.offset()]))
            count--;
        if (count > 0)
            deleteText(textNode, offset, count);
    }

    if (offset > 0 && offset <= text.length() - 1 && !isWS(text[offset]) && !isWS(text[offset - 1])) {

        insertText(textNode, offset, " ");
        return;
    }

    if (text.length() >= 2 && offset >= 2 && isNBSP(text[offset - 2]) && isNBSP(text[offset - 1])) {


        insertText(textNode, offset - 1, " ");
        return;
    }


    insertText(textNode, offset, nonBreakingSpaceString());
}
