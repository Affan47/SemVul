slotViewCleared()
{
    if (QScrollArea *view = qobject_cast<QScrollArea*>(m_widget)) {
#ifdef DEBUG_LAYOUT
        kDebug(6031) << "frame is a scrollarea!";
#endif
        if(!element()->frameBorder || !((static_cast<HTMLFrameSetElementImpl *>(element()->parentNode()))->frameBorder()))
            view->setFrameStyle(QFrame::NoFrame);
        if(KHTMLView *htmlView = qobject_cast<KHTMLView*>(view)) {
#ifdef DEBUG_LAYOUT
            kDebug(6031) << "frame is a KHTMLview!";
#endif
	    htmlView->setVerticalScrollBarPolicy(element()->scrolling );
	    htmlView->setHorizontalScrollBarPolicy(element()->scrolling );
            if(element()->marginWidth != -1) htmlView->setMarginWidth(element()->marginWidth);
            if(element()->marginHeight != -1) htmlView->setMarginHeight(element()->marginHeight);
        } else {

    	    view->setVerticalScrollBarPolicy(element()->scrolling );
	    view->setHorizontalScrollBarPolicy(element()->scrolling );
        }
    }

}
