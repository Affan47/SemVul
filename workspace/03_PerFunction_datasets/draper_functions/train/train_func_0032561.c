detach(KJS::Interpreter* interp)
{
    assert(interp);


    InterpreterContext* ctx = m_contexts[interp];
    assert (!m_activeSessionCtxs.contains(ctx));


    QList<DebugDocument::Ptr> docs = m_docsForIntrp[interp];

    foreach (DebugDocument::Ptr doc, docs)
        cleanupDocument(doc);

    m_docsForIntrp.remove(interp);

    delete m_contexts.take(interp);
    resetTimeoutsIfNeeded();

    KJS::Debugger::detach(interp);
}
