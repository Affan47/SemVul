close (void)
{
  for (--n_; n_ >= 0; --n_)
    {
#if defined (ACE_LACKS_STRUCT_DIR)


      ACE_OS::free (this->namelist_[n_]->d_name);
#endif
      ACE_OS::free (this->namelist_[n_]);
    }

  ACE_OS::free (this->namelist_);
  this->namelist_ = 0;
  return 0;
}
