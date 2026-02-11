parseText()
{
    DOMString text = "";

    for (NodeImpl *c = firstChild(); c != 0; c = c->nextSibling()) {
	if ((c->nodeType() == Node::TEXT_NODE) ||
	    (c->nodeType() == Node::CDATA_SECTION_NODE) ||
	    (c->nodeType() == Node::COMMENT_NODE))
	    text += c->nodeValue();
    }

    if (m_sheet) {
        m_sheet->deref();
        m_sheet = 0;
    }

    m_loading = false;
    if (m_type.isEmpty() || m_type == "text/css")
    {
        MediaListImpl* media = new MediaListImpl((CSSStyleSheetImpl*)0, m_media, true);
        media->ref();
        khtml::MediaQueryEvaluator screenEval("screen", true);
        khtml::MediaQueryEvaluator printEval("print", true);
        if (screenEval.eval(media) || printEval.eval(media)) {
            document()->addPendingSheet();
            m_loading = true;
            m_sheet = new CSSStyleSheetImpl(this);
            m_sheet->ref();
            m_sheet->parseString( text, !document()->inCompatMode() );
            m_sheet->setMedia( media );
            m_sheet->setTitle( getAttribute(ATTR_TITLE) );
            m_loading = false;
        }
        media->deref();
    }

    if (!isLoading() && m_sheet)
        document()->styleSheetLoaded();
}
