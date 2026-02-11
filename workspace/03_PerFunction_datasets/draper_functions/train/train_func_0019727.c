to_wstring () const
      {
        return ACE_Ascii_To_Wide (this->to_string().c_str ()).wchar_rep ();
      }
