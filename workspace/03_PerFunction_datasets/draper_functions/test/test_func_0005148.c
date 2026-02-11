finishCloneNode( ElementImpl* clone, bool deep )
{

    if (namedAttrMap || m_needsStyleAttributeUpdate)
	clone->attributes()->copyAttributes(attributes(true));

    assert( !m_needsStyleAttributeUpdate );


    if (m_style.inlineDecls) {
        if (m_hasCombinedStyle) {
            if (!clone->m_hasCombinedStyle)
                clone->createNonCSSDecl();
            if (m_style.combinedDecls->inlineDecls)
                *(clone->getInlineStyleDecls()) = *m_style.combinedDecls->inlineDecls;
            *clone->m_style.combinedDecls->nonCSSDecls = *m_style.combinedDecls->nonCSSDecls;
        } else {
            *(clone->getInlineStyleDecls()) = *m_style.inlineDecls;
        }
    }


    clone->copyNonAttributeProperties(this);

    if (deep)
        cloneChildNodes(clone);


    clone->setHTMLCompat(htmlCompat());
}
