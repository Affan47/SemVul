clear() {


    if (m_script) {
#ifdef KJS_DEBUGGER
        if (m_debugWindow)
            m_debugWindow->clearInterpreter(m_script);
#endif
        m_script->clear();

        Window *win = static_cast<Window *>(m_script->globalObject());
        if (win) {
            win->clear( m_script->globalExec() );

            m_script->globalObject()->put(m_script->globalExec(),
                                        "debug", new TestFunctionImp(), Internal);
            if ( win->part() )
            applyUserAgent();
    }


    JSLock::lock();
    while (Interpreter::collect())
	    ;
    JSLock::unlock();
  }

#ifdef KJS_DEBUGGER

  if (m_debugWindow && !m_debugEnabled) {
    m_debugWindow->detach(m_script);
    m_debugWindow = 0;
  }
#endif
}
