enterDebugSession(KJS::ExecState *exec, DebugDocument *document, int line)
{
    Q_UNUSED(document);
    Q_UNUSED(line);


    if (!isVisible())
        show();

    m_activeSessionCtxs.push(m_contexts[exec->dynamicInterpreter()]);
    ctx()->mode   = Normal;
    m_breakAtNext = false;
    m_stopAct->setChecked(false);

    setUIMode(Stopped);
    enterLoop();
}
