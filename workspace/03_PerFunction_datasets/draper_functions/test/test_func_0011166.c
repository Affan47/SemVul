executeScript(const QString& filename, int baseLine, const DOM::Node& n, const QString& script)
{
#ifdef KJS_VERBOSE

  kDebug(6070) << "executeScript: caller='" << objectName() << "' filename=" << filename << " baseLine=" << baseLine ;
#endif
  KJSProxy *proxy = jScript();

  if (!proxy || proxy->paused())
    return QVariant();


  (void)proxy->interpreter();

  KJS::Completion comp;

  QVariant ret = proxy->evaluate(filename, baseLine, script, n, &comp);


  if (comp.complType() == KJS::Throw && comp.value()) {
    KJSErrorDlg *dlg = jsErrorExtension();
    if (dlg) {
      QString msg = KJSDebugger::DebugWindow::exceptionToString(
                              proxy->interpreter()->globalExec(), comp.value());
      dlg->addError(i18n("<qt><b>Error</b>: %1: %2</qt>",
                         Qt::escape(filename), Qt::escape(msg)));
    }
  }


  if ( !d->m_redirectURL.isEmpty() && d->m_delayRedirect == -1 )
  {
    kDebug(6070) << "executeScript done, handling immediate redirection NOW";

    khtml::Tokenizer* t = d->m_doc->tokenizer();
    if(t)
      t->abort();
    d->m_redirectionTimer.setSingleShot( true );
    d->m_redirectionTimer.start( 0 );
  }

  return ret;
}
