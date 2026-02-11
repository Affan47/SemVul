setClipRect(QScriptContext *ctx, QScriptEngine *eng)
{
    DECLARE_SELF(QPainter, setClipRect);

    if (ctx->argumentCount() >= 4) {

        self->setClipRect(ctx->argument(0).toInt32(),
                          ctx->argument(1).toInt32(),
                          ctx->argument(2).toInt32(),
                          ctx->argument(3).toInt32());
    } else if (ctx->argumentCount() >= 1) {

        self->setClipRect(qscriptvalue_cast<QRectF>(ctx->argument(0)));
    }
    return eng->undefinedValue();
}
