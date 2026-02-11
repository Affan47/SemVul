showSuppressedWindows()
{
  KHTMLPart *part = qobject_cast<KHTMLPart*>(m_frame->m_part);
  KJS::Interpreter *interpreter = part->jScript()->interpreter();
  ExecState *exec = interpreter->globalExec();

  QList<SuppressedWindowInfo> suppressedWindowInfo = m_suppressedWindowInfo;
  m_suppressedWindowInfo.clear();
  foreach ( const SuppressedWindowInfo &info, suppressedWindowInfo ) {
    executeOpenWindow(exec, info.url, info.frameName, info.features);
  }
}
