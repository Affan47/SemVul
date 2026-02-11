Query(const Arguments& args) {
  HandleScope scope;
  Channel *c = ObjectWrap::Unwrap<Channel>(args.Holder());
  assert(c);

  if (!args[0]->IsString()) {
    return ThrowException(Exception::TypeError(
          String::New("First argument must be a name")));
  }

  if (!args[1]->IsInt32()) {
    return ThrowException(Exception::TypeError(
          String::New("Second argument must be a query type")));
  }

  if (!args[2]->IsFunction()) {
    return ThrowException(Exception::TypeError(
          String::New("Third argument must be a callback")));
  }

  String::Utf8Value name(args[0]->ToString());
  int type = args[1]->Int32Value();
  QueryArg::ParseAnswerCb parse_cb;

  switch(type) {
    case ns_t_a:
      parse_cb = ParseAnswerA;
      break;

    case ns_t_aaaa:
      parse_cb = ParseAnswerAAAA;
      break;

    case ns_t_mx:
      parse_cb = ParseAnswerMX;
      break;

    case ns_t_ns:
      parse_cb = ParseAnswerNS;
      break;

    case ns_t_txt:
      parse_cb = ParseAnswerTXT;
      break;

    case ns_t_srv:
      parse_cb = ParseAnswerSRV;
      break;

    case ns_t_cname:
      parse_cb = ParseAnswerCNAME;
      break;

    case ns_t_ptr:

      int length, family;
      char address_b[sizeof(struct in6_addr)];

      if (inet_pton(AF_INET, *name, &address_b) == 1) {
        length = sizeof(struct in_addr);
        family = AF_INET;
      } else if (inet_pton(AF_INET6, *name, &address_b) == 1) {
        length = sizeof(struct in6_addr);
        family = AF_INET6;
      } else {
        return ThrowException(Exception::Error(String::New("Invalid IP address")));
      }

      ares_gethostbyaddr(c->channel, address_b, length, family, HostByAddrCb, cb_persist(args[2]));

      return Undefined();

    default:
      return ThrowException(Exception::Error(
            String::New("Unsupported query type")));
  }

  QueryArg *query_arg = new QueryArg(args[2], parse_cb);

  ares_query(c->channel, *name, ns_c_in, type, QueryCb, query_arg);

  return Undefined();
}
