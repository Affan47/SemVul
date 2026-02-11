innerPart( khtml::RenderObject *ro ) {
    if (!ro || !ro->isWidget() || ro->isFormElement())
        return 0;
    KHTMLView* v = qobject_cast<KHTMLView*>( static_cast<khtml::RenderWidget*>(ro)->widget() );
    return v ? v->part() : 0;
}
