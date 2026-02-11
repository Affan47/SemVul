remove_TkFileHandler (ACE_HANDLE handle)
{
  ACE_TRACE ("ACE_TkReactor::remove_TkFileHandler");

  ACE_TkReactorID *TkID = this->ids_;

  if (TkID)
    {
      if (TkID->handle_ == handle)
        {
          ::Tk_DeleteFileHandler (TkID->handle_);
          this->ids_ = TkID->next_;
          delete TkID;
          return;
        }

      ACE_TkReactorID *NextID = TkID->next_;

      while (NextID)
        {
          if (NextID->handle_ == handle)
            {
              ::Tk_DeleteFileHandler (NextID->handle_);
              TkID->next_ = NextID->next_;
              delete NextID;
              return;
            }
          else
            {
              TkID = NextID;
              NextID = NextID->next_;
            }
        }
    }
}
