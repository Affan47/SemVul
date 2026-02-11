process(const ClientHTTPAttributes &reqattr,
                         PayloadRawInterface *request,
                         HTTPClientInfo *info, PayloadRawInterface **response) {
    MessagePayload* mresp = NULL;
    MCC_Status r = process(reqattr.method_,reqattr.path_,reqattr.attributes_,
                           reqattr.range_start_,reqattr.range_end_,
                           (MessagePayload*)request,info,&mresp);
    if (mresp != NULL) {
      try {
        *response = dynamic_cast<PayloadRawInterface*>(mresp);
      } catch (std::exception&) {
        delete mresp;
      }
    }
    return r;
  }
