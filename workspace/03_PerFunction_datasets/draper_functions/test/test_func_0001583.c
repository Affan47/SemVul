setStringValue( unsigned short stringType, const DOMString &stringValue )
{
    int exceptioncode = 0;
    if(impl)
        ((CSSPrimitiveValueImpl *)impl)->setStringValue( stringType, stringValue, exceptioncode );
    if ( exceptioncode >= CSSException::_EXCEPTION_OFFSET )
	throw CSSException( exceptioncode - CSSException::_EXCEPTION_OFFSET );
    if ( exceptioncode )
	throw DOMException( exceptioncode );

}
