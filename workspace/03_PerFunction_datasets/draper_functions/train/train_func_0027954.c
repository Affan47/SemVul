Chdir(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 1 || !args[0]->IsString()) {
    return ThrowException(Exception::Error(String::New("Bad argument.")));
  }

  String::Utf8Value path(args[0]->ToString());

  uv_err_t r = uv_chdir(*path);

  if (r.code != UV_OK) {
    return ThrowException(UVException(r.code, "uv_chdir"));
  }

  return Undefined();
}
