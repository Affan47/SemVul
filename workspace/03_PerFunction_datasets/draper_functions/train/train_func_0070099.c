requestStyleSheet( const DOM::DOMString &url, const QString& charset,
						   const char *accept, bool userSheet )
{
    DOCLOADER_SECCHECK(!userSheet);

    CachedCSSStyleSheet* s = Cache::requestObject<CachedCSSStyleSheet, CachedObject::CSSStyleSheet>( this, fullURL, accept );
    if ( s && !charset.isEmpty() ) {
        s->setCharsetHint( charset );
    }
    return s;
}
