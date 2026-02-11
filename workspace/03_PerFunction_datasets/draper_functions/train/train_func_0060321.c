cleanMultimodel()
{
  if (m_numModels) {

    m_loadedCache->refCount--;


    if (m_loadedCache->refCount == 0) {

      multiModelCache *ptr = s_modelCache;


      if (m_loadedCache == s_modelCache) {
        s_modelCache = m_loadedCache->next;
        delete m_loadedCache;
      }
      else {
        while (ptr && ptr->next != m_loadedCache) ptr = ptr->next;
        if (!ptr) error("unable to find model cache!");
        else {
          ptr->next = m_loadedCache->next;
          delete m_loadedCache;
        }
      }
    }

    m_loadedCache = NULL;
    m_numModels = 0;
  }
}
