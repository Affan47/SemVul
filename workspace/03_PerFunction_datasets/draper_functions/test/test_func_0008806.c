Base64Encode(const std::string& data) {
    xmlChar *b64_out = NULL;
    b64_out = xmlSecBase64Encode((xmlChar*)(data.c_str()), data.length(), 0);
    std::string ret;
    if(b64_out != NULL) {
      ret.append((char*)b64_out);
      xmlFree(b64_out);
    }
    return ret;
  }
