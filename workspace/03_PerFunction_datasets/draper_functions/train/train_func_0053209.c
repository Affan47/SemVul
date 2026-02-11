set_content_length(int length)
      {
        if (length == UNKNOWN_CONTENT_LENGTH)
          {
            this->remove (CONTENT_LENGTH);
          }
        else
          {
            char buf[32];
            this->set (CONTENT_LENGTH,
                       ACE_OS::itoa (length, buf, 10));
          }
      }
