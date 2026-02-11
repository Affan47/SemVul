insert (ACE_Static_Svc_Descriptor *stsd)
{
  if (this->static_svcs_ == 0)
    ACE_NEW_RETURN (this->static_svcs_,
                    ACE_STATIC_SVCS,
                    -1);

  return this->static_svcs_->insert (stsd);
}
