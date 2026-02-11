sourceParsed(ExecState *exec, int sourceId, const UString& jsSourceURL,
                               const UString &source, int startingLineNumber, int errorLine, const UString &)
{
    Q_UNUSED(exec);

    kDebug() << "sourceId: " << sourceId
             << "sourceURL: " << jsSourceURL.qstring()
             << "startingLineNumber: " << startingLineNumber
             << "errorLine: " << errorLine;

    QString sourceURL = jsSourceURL.qstring();

    QString qsource =  source.qstring();


    DebugDocument::Ptr document;


    foreach (DebugDocument::Ptr cand, m_openDocuments)
    {
        if (cand->isMarkedReload() && cand->url() == sourceURL && cand->baseLine() == startingLineNumber)
            document = cand;
    }


    if (!document)
    {


        QString uiURL = sourceURL;

        if (uiURL.isEmpty())
        {

            foreach (InterpreterContext* ic, m_contexts)
            {
                if (!ic->execContexts.isEmpty() && ic->execContexts.top() == exec)
                {
                    uiURL = ic->callStack.top().doc->url();
                    break;
                }
            }

        }

        document = new DebugDocument(exec->dynamicInterpreter(), uiURL,
                                     sourceId, startingLineNumber, qsource);

        connect(document.get(), SIGNAL(documentDestroyed(KJSDebugger::DebugDocument*)),
                this, SLOT(documentDestroyed(KJSDebugger::DebugDocument*)));
    }
    else
    {

        document->reloaded(sourceId, qsource);
    }

    m_docsForIntrp[exec->dynamicInterpreter()].append(document);


    m_scripts->addDocument(document.get());


    m_docForSid[sourceId] = document;

    if (qsource.contains("function"))
        document->setHasFunctions();

    return shouldContinue(m_contexts[exec->dynamicInterpreter()]);
}
