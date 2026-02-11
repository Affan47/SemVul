New (const Arguments& args) {
    HandleScope scope;

    Hmac *hmac = new Hmac();
    hmac->Wrap(args.This());
    return args.This();
  }
