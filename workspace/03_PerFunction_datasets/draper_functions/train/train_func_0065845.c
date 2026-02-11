evaluate(const QByteArray& code)
{
    if( ! d->m_engine && ! d->init() ) {
        d->handleException();
        return QVariant();
    }

    QScriptValue result = d->m_engine->evaluate(code);
    if( d->m_engine->hasUncaughtException() ) {
        d->handleException();
        return QVariant();
    }
    return result.toVariant();
}
