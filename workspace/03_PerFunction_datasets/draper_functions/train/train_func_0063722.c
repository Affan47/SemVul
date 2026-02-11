popOneBlock(bool delBlock)
{
    HTMLStackElem *Elem = blockStack;


#ifndef PARSER_DEBUG
    if(!Elem) return;
#else
    kDebug( 6035 ) << "popping block: " << getParserPrintableName(Elem->id) << "(" << Elem->id << ")";
#endif

#if SPEED_DEBUG < 1
    if((Elem->node != current)) {
        if (current->maintainsState() && document){
            document->registerMaintainsState(current);
            document->attemptRestoreState(current);
        }
        current->close();
    }
#endif

    removeForbidden(Elem->id, forbiddenTag);

    blockStack = Elem->next;


    m_inline = Elem->m_inline;

    if (current->id() == ID_FORM && form && inStrayTableContent)
        form->setMalformed(true);

    setCurrent( Elem->node );

    if (Elem->strayTableContent)
        inStrayTableContent--;

    if (delBlock)
        delete Elem;
}
