caretMinOffset() const
{
    RenderText *r = static_cast<RenderText *>(renderer());
    return r && r->isText() ? r->convertToDOMPosition(r->caretMinOffset()) : 0;
}
