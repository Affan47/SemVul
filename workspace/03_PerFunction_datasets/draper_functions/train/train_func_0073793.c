add_authenticator (const ACE_CString& auth_id,
                                             AuthenticatorBase* authenticator)
      {
        if (URL_INetAuthBase::authenticators_.find (auth_id) == -1)
          {
            return URL_INetAuthBase::authenticators_.bind (auth_id,
                                                           authenticator_ptr (authenticator)) == 0;
          }
        return false;
      }
