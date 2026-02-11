GetExtension(const std::string& name) {
    std::string res;
    if(cert_ == NULL) return res;
    int num;
    if ((num = X509_get_ext_count(cert_)) > 0) {
      for (int i = 0; i < num; i++) {
        X509_EXTENSION *ext;
        const char *extname;

        ext = X509_get_ext(cert_, i);
        extname = OBJ_nid2sn(OBJ_obj2nid(X509_EXTENSION_get_object(ext)));

        if (strcmp(extname, name.c_str()) == 0) {
          X509V3_EXT_METHOD *method;
          STACK_OF(CONF_VALUE) *val;
          CONF_VALUE *nval;
          void *extstr = NULL;
#if (OPENSSL_VERSION_NUMBER >= 0x0090800FL)
          const unsigned char *ext_value_data;
#else
          unsigned char *ext_value_data;
#endif


          if (!(method = (X509V3_EXT_METHOD *)(X509V3_EXT_get(ext)))) break;

          ext_value_data = ext->value->data;


          if (method->it) {

               extstr = ASN1_item_d2i(NULL, &ext_value_data, ext->value->length,
                                      ASN1_ITEM_ptr(method->it));
          }
          else {

               extstr = method->d2i(NULL, &ext_value_data, ext->value->length);
          }

          val = method->i2v(method, extstr, NULL);
          for (int j = 0; j < sk_CONF_VALUE_num(val); j++) {
            nval = sk_CONF_VALUE_value(val, j);
            std::string name = nval->name;
            std::string val = nval->value;
            if(!val.empty()) res = name + ":" + val;
            else res = name;
          }
        }
      }
    }
    return res;
  }
