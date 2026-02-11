detach(RenderArena* renderArena, bool noRemove)
{
    if (!noRemove) remove();

#ifndef NDEBUG
    inInlineTextBoxDetach = true;
#endif
    delete this;
#ifndef NDEBUG
    inInlineTextBoxDetach = false;
#endif


    renderArena->free(*(size_t *)this, this);
}
