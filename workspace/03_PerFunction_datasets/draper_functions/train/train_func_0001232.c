manhattanLength(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QPoint, manhattanLength);
    return QScriptValue(eng, self->manhattanLength());
}
