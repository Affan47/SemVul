createGemWindow(void){
  if(!m_context) {
    try {
      m_pimpl->mycontext = new gem::Context();
    } catch (GemException&x) {
      m_context=NULL;
      error("%s", x.what());
      return false;
    }
    m_context=m_pimpl->mycontext;
  } else {
    m_pimpl->mycontext = NULL;
  }

  m_pimpl->dispatch();

  return true;
}
