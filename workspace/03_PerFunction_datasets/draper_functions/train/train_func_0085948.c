push_SQ(SQueue* Line, void* val)
{
    if(Line->LSize != Line->PSize) {
        Line->OP[Line->BPos] = val;
        if(Line->BPos == Line->PSize - 1) {
            Line->BPos = 0;
        } else {
            Line->BPos++;
        }
        Line->LSize++;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
