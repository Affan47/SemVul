after_read (const char_type* , int length_read)
      {
        if (this->read_length_ == 0)
          {
            this->in_length_ = this->response ().get_content_length ();
          }
        this->read_length_ += length_read;
        std::cout << "\r [" << this->read_length_ << '/';
        if (this->in_length_ != ACE::HTTP::Response::UNKNOWN_CONTENT_LENGTH)
          {
            std::cout << this->in_length_ << "] " << ((this->read_length_ * 100) / this->in_length_) << "%";
          }
        else
          std::cout << "???]";
        std::cout.flush ();
      }
