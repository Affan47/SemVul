set_credentials(const ACE_CString& scheme, const ACE_CString& auth_info)
      {
        ACE_CString val (scheme);
        val += " ";
        val += auth_info;
        this->set (AUTHORIZATION, val);
      }
