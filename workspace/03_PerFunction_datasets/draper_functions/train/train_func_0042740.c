shutdown()
{
  if(m_notebook != NULL) {
    gnote::notebooks::NotebookManager::obj().delete_notebook(m_notebook);
    m_notebook.reset();
    m_initialized = false;
  }
}
