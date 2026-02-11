filteredStatusFunc(void *baton_,
                     const char *path,
                     svn_wc_status2_t *status)
  {
    StatusBaton * baton = static_cast<StatusBaton *>(baton_);


    if (0 == status)
      return;

    bool useStatus = false;

    bool isUnversioned = 0 == status->entry;
    if (isUnversioned)
    {
      if (baton->filter.showUnversioned)
        useStatus = true;
    }
    else
    {
      bool isUnmodified =
        ((svn_wc_status_normal == status->text_status) &&
         (svn_wc_status_normal == status->prop_status));

      if (isUnmodified)
      {
        if (baton->filter.showUnmodified)
          useStatus = true;
      }
      else
      {


        if (baton->filter.showModified)
          useStatus = true;
        else if (baton->filter.showConflicted)
        {
          if (svn_wc_status_conflicted == status->text_status)
            useStatus = true;
        }
      }
    }

    if (useStatus)
      baton->entries.push_back(Status(path, status));
  }
