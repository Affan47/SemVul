SetPrivateKey(const Arguments& args) {
    HandleScope scope;

    DiffieHellman* diffieHellman =
      ObjectWrap::Unwrap<DiffieHellman>(args.This());

    if (!diffieHellman->initialised_) {
      return ThrowException(Exception::Error(
            String::New("Not initialized")));
    }

    if (args.Length() == 0) {
      return ThrowException(Exception::Error(
            String::New("First argument must be private key")));
    } else {
      if (args[0]->IsString()) {
        char* buf;
        int len;
        if (args.Length() > 1) {
          len = DecodeWithEncoding(args[0], args[1], &buf);
        } else {
          len = DecodeBinary(args[0], &buf);
        }
        if (len == -1) {
          delete[] buf;
          return ThrowException(Exception::Error(
                String::New("Invalid argument")));
        }
        diffieHellman->dh->priv_key =
          BN_bin2bn(reinterpret_cast<unsigned char*>(buf), len, 0);
        delete[] buf;
      } else if (Buffer::HasInstance(args[0])) {
        Local<Object> buffer = args[0]->ToObject();
        diffieHellman->dh->priv_key =
          BN_bin2bn(
            reinterpret_cast<unsigned char*>(Buffer::Data(buffer)),
            Buffer::Length(buffer), 0);
      } else {
        return ThrowException(Exception::Error(
              String::New("First argument must be private key")));
      }
    }

    return args.This();
  }
