handle_get_request (
        const URL& ftp_url,
        bool binary)
      {
        if (this->initialize_connection (ftp_url.get_host (),
                                         ftp_url.get_port ()))
          {
            bool rc = true;
            if (this->session ()->is_new_connection () ||
                (!ftp_url.get_user_info ().empty () &&
                    ftp_url.get_user_info () != this->current_user_))
              {
                if (!this->session ()->is_new_connection ())
                  rc = this->logout ();

                if (rc)
                  {
                    ACE_CString user = ftp_url.get_user_info ().empty () ?
                        anonymous_user_ : ftp_url.get_user_info ();
                    ACE_CString password = user;
                    rc = this->handle_credentials (ftp_url, user, password);
                    if (rc) rc = this->login (user, password);
                  }
              }

            if (rc) rc = this->finish_transfer ();

            if (rc)
              {
                stream_type* data_stream =
                    this->start_download (ftp_url.get_path (), binary);
                if (data_stream)
                  {


                    this->in_data_stream_.set_stream (data_stream);
                  }
                else
                  {
                    rc = false;
                  }
              }

            if (!rc)
              {
                this->close_connection ();

                this->handle_request_error(ftp_url);
              }
          }
        else
          {
            this->handle_connection_error (ftp_url);
          }

        return this->response_stream ();
      }
