propertySetFree(CssPropertySet *p){
    int i;
    if( !p ) return;
    for (i = 0; i < p->n; i++) {
        propertyFree(p->a[i].pProp);
    }
    HtmlFree(p->a);
    HtmlFree(p);
}
