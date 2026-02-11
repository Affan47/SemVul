extractQByteArray( KJS::ExecState *exec, KJS::JSValue *value, const QByteArray &defaultValue  )
{
    if( !value )
        return defaultValue;
    return toQString(value->toString(exec)).toLatin1();
}
