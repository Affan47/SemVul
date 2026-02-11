add( StyleSheetImpl* s )
{
    if (managerDocument)
        managerDocument->ensureStyleSheetListUpToDate();


    if ( !styleSheets.contains( s ) ) {
        s->ref();
        styleSheets.append( s );
    }
}
