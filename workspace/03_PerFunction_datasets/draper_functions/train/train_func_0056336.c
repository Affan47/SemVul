ShExpMatch (QScriptContext* context, QScriptEngine* engine)
    {
        if (context->argumentCount() != 2) {
            return engine->undefinedValue();
        }

        QRegExp pattern(context->argument(1).toString(), Qt::CaseSensitive, QRegExp::Wildcard);
        return engine->toScriptValue(pattern.exactMatch(context->argument(0).toString()));
    }
