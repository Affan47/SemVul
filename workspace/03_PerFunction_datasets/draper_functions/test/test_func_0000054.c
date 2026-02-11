utc_to_asn1time(const Time& t) {

    std::string t_str = t.str(MDSTime);
    if(t_str.length() < 2) return NULL;
    ASN1_UTCTIME* s = ASN1_UTCTIME_new();
    if(!s) return NULL;
    if(ASN1_UTCTIME_set_string(s,(char*)(t_str.c_str()+2))) return s;
    ASN1_UTCTIME_free(s);
    return NULL;


  }
