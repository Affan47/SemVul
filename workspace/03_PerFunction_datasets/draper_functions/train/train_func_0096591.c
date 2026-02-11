GenerateRequest(const char* filename, bool if_der) {
    BIO *out = BIO_new(BIO_s_file());
    if(!out) {
      CredentialLogger.msg(ERROR, "Can not create BIO for request");
      LogError(); return false;
    }
    if (!(BIO_write_filename_User(out, filename))) {
      CredentialLogger.msg(ERROR, "Can not set writable file for request BIO");
      LogError(); BIO_free_all(out); return false;
    }

    if(GenerateRequest(out,if_der)) {
      CredentialLogger.msg(INFO, "Wrote request into a file");
    }
    else {
      CredentialLogger.msg(ERROR, "Failed to write request into a file");
      BIO_free_all(out); return false;
    }

    BIO_free_all(out);
    return true;
  }
