process()
{
    if (!inDocument())
        return;

    QString type = getAttribute(ATTR_TYPE).string().toLower();
    QString rel = getAttribute(ATTR_REL).string().toLower();

    KHTMLPart* part = document()->part();


    if ( part && rel.contains("icon") && !m_url.isEmpty() && !part->parentPart())
        part->browserExtension()->setIconUrl( KUrl(m_url.string()) );


    else if (!m_isDisabled && rel.contains("stylesheet")) {


        khtml::MediaQueryEvaluator allEval(true);
        khtml::MediaQueryEvaluator screenEval("screen", true);
        khtml::MediaQueryEvaluator printEval("print", true);
        MediaListImpl* media = new MediaListImpl((CSSStyleSheetImpl*)0, m_media, true);
        media->ref();
        if (allEval.eval(media) || screenEval.eval(media) || printEval.eval(media)) {


            m_alternate = rel.contains("alternate");
            if (!isAlternate())
                document()->addPendingSheet();

            QString chset = getAttribute( ATTR_CHARSET ).string();


            if (chset.isEmpty() && part) chset = part->encoding();
            if (m_cachedSheet) {
                if (m_loading)
                    document()->styleSheetLoaded();
		m_cachedSheet->deref(this);
            }
            m_loading = true;
            m_cachedSheet = document()->docLoader()->requestStyleSheet(m_url, chset);
            if (m_cachedSheet) {
                m_isCSSSheet = true;
		m_cachedSheet->ref(this);
            }
            else if (!isAlternate()) {

                m_loading = false;
                document()->styleSheetLoaded();
            }
        }
        media->deref();
    }
    else if (m_sheet) {

	m_sheet->deref();
	m_sheet = 0;
        m_isCSSSheet = false;
	document()->updateStyleSelector();
    }
}
