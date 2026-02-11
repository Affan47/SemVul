get4Values( const int* properties ) const
{
    DOMString res;
    for ( int i = 0 ; i < 4 ; ++i ) {
        if (!isPropertyImplicit(properties[i])) {
            CSSValueImpl* value = getPropertyCSSValue( properties[i] );
            if ( !value ) {
                return DOMString();
            }
            if ( i > 0 )
                res += " ";
            res += value->cssText();
        }
    }
    return res;
}
