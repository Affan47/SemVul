evaluate(QString filename, int baseLine,
                                const QString&str, const DOM::Node &n, Completion *completion) {
  ++m_running;


  initScript();


  bool inlineCode = filename.isNull();


#ifdef KJS_DEBUGGER
    if (inlineCode)
        filename = "(unknown file)";
    if (m_debugWindow)
        m_debugWindow->attach(m_script);
#else
    Q_UNUSED(baseLine);
#endif

  m_script->setInlineCode(inlineCode);
  Window* window = Window::retrieveWindow( m_frame->m_part );
  KJS::JSValue *thisNode = n.isNull() ? Window::retrieve( m_frame->m_part ) : getDOMNode(m_script->globalExec(),n.handle());

  UString code( str );

  m_script->startCPUGuard();
  Completion comp = m_script->evaluate(filename, baseLine, code, thisNode);
  m_script->stopCPUGuard();

  bool success = ( comp.complType() == KJS::Normal ) || ( comp.complType() == ReturnValue );

  if (completion)
    *completion = comp;

#ifdef KJS_DEBUGGER

#endif

  window->afterScriptExecution();

  --m_running;


  if (success && comp.value())
    return ValueToVariant( m_script->globalExec(), comp.value());
  else
  {
    if ( comp.complType() == Throw )
    {
        UString msg = comp.value()->toString(m_script->globalExec());
        kDebug(6070) << "WARNING: Script threw exception: " << msg.qstring();
    }
    return QVariant();
  }
}
