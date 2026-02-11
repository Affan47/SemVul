exit() const
{
   ::lt_dlexit();

   if (m_pLoadedModuleHandle)
      ::lt_dlclose(m_pLoadedModuleHandle);
}
