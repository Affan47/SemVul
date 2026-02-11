OnHeadersComplete(struct http_parser* _parser)
  {
    unsigned char method_code = _parser->method;
    switch(method_code) {
      case HTTP_DELETE:
        _method = METHOD_HTTP_DELETE;
        break;
      case HTTP_GET:
        _method = METHOD_HTTP_GET;
        break;
      case HTTP_HEAD:
        _method = METHOD_HTTP_HEAD;
        break;
      case HTTP_POST:
        _method = METHOD_HTTP_POST;
        break;
      case HTTP_PUT:
        _method = METHOD_HTTP_PUT;
        break;
      default:

        return 2;
        break;
    }

    qDebug() << "OnHeadersComplete() Method:" << (int)_method;
    return 0;
  }
