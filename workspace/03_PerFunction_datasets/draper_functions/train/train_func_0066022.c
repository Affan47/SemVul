VerifyUpdate(char* data, int len) {
    if (!initialised_) return 0;
    EVP_VerifyUpdate(&mdctx, data, len);
    return 1;
  }
