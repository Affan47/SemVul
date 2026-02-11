pop_SQ(SQueue* Line)
{
    if(Line->LSize) {
        void* temp = Line->OP[Line->FPos];
        if(Line->FPos == Line->PSize - 1) {
            Line->FPos = 0;
        } else {
            Line->FPos++;
        }
        Line->LSize--;
        return temp;
    }
    return NULL;
}
