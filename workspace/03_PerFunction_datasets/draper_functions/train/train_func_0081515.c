open (const ACE_TCHAR *file_name,
                   int flags,
                   mode_t perms,
                   LPSECURITY_ATTRIBUTES sa)
{
  ACE_TRACE ("ACE_Mem_Map::open");

#if defined (INTEGRITY)  || defined (__QNXNTO__) || defined (ACE_VXWORKS)
  this->handle_ = ACE_OS::shm_open (file_name, flags, perms, sa);
#elif defined (ACE_OPENVMS)
  ACE_OSCALL (::open (file_name, flags, perms, "shr=get,put,upd"), ACE_HANDLE, -1, this->handle_);
#else
  this->handle_ = ACE_OS::open (file_name, flags, perms, sa);
#endif

  if (this->handle_ == ACE_INVALID_HANDLE)
    return -1;
  else
    {
      ACE_OS::strsncpy (this->filename_,
                        file_name,
                        MAXPATHLEN);

      this->close_handle_ = true;
      return 0;
    }
}
