parse_ext_address (const ACE_CString& str, ACE_INET_Addr& addr)
      {
        static const int eof_ = std::char_traits<char>::eof ();

        ACE::IOS::CString_IStream sis (str);
        sis.ignore (str.length (), '(');
        int ch = sis.get ();
        if (ch != eof_)
          {
            int delim = ch;
            sis.ignore (str.length (), delim);
            sis.ignore (str.length (), delim);
            if (sis.peek () != eof_)
              {
                u_short port = 0;
                sis >> port;
                addr.set (port, this->session ()->get_host ().c_str ());
                return true;
              }
          }
        return false;
      }
