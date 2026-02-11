NewParser(void)
{
    Parser p;

    if(ParserInit() == -1)
	return 0;

    p = Malloc(sizeof(*p));
    if(!p)
	return 0;
    p->state = PS_prolog1;
    p->document_entity = 0;
    p->have_dtd = 0;
    p->standalone = SDD_unspecified;
    p->flags = 0;
    p->source = 0;
    clear_xbit(&p->xbit);
#ifndef FOR_LT
    p->xbit.nchildren = 0;
    p->xbit.children = 0;
    p->xbit.parent = 0;
#endif
    p->pbufsize = p->pbufnext = 0;
    p->pbuf = 0;
    p->peeked = 0;
    p->dtd = NewDtd();
    p->dtd_callback = p->warning_callback = 0;
    p->entity_opener = 0;
    p->callback_arg = 0;
    p->external_pe_depth = 0;

    p->element_stack = 0;
    p->element_stack_alloc = 0;
    p->element_depth = 0;

    ParserSetFlag(p, XMLPiEnd, 1);
    ParserSetFlag(p, XMLEmptyTagEnd, 1);
    ParserSetFlag(p, XMLPredefinedEntities, 1);
    ParserSetFlag(p, XMLExternalIDs, 1);
    ParserSetFlag(p, XMLMiscWFErrors, 1);
    ParserSetFlag(p, ErrorOnUnquotedAttributeValues, 1);
    ParserSetFlag(p, XMLLessThan, 1);
    ParserSetFlag(p, IgnoreEntities, 0);
    ParserSetFlag(p, ExpandGeneralEntities, 1);
    ParserSetFlag(p, ExpandCharacterEntities, 1);
    ParserSetFlag(p, NormaliseAttributeValues, 1);
    ParserSetFlag(p, WarnOnUndefinedElements, 1);
    ParserSetFlag(p, WarnOnUndefinedAttributes, 1);
    ParserSetFlag(p, WarnOnRedefinitions, 1);
    ParserSetFlag(p, TrustSDD, 1);
    ParserSetFlag(p, ReturnComments, 1);
    ParserSetFlag(p, CheckEndTagsMatch, 1);

    return p;
}
