setenv_i (ACE_TCHAR *assignment,
                               size_t len)
{

  ++len;


  if (environment_argv_index_ == max_environ_argv_index_
      || (len + environment_buf_index_) >= environment_buf_len_)
    return -1;


  ACE_OS::memcpy (environment_buf_ + environment_buf_index_,
                  assignment,
                  len * sizeof (ACE_TCHAR));


  environment_argv_[environment_argv_index_++] =
    environment_buf_ + environment_buf_index_;
  environment_argv_[environment_argv_index_] = 0;


  environment_buf_index_ += len;


  environment_buf_[environment_buf_index_] = '\0';
  return 0;
}
