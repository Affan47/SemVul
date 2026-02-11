adjusted(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QRectF, adjusted);
    qreal dx1 = ctx->argument(0).toNumber();
    qreal dy1 = ctx->argument(1).toNumber();
    qreal dx2 = ctx->argument(2).toNumber();
    qreal dy2 = ctx->argument(3).toNumber();

    QRectF tmp = self->adjusted(dx1, dy1, dx2, dy2);
    return qScriptValueFromValue(eng, tmp);
}
