SetProxyPeriod(X509* tosign, X509* issuer, const Time& start, const Period& lifetime) {
    Time pt1 = start;
    Time pt2 = start + lifetime;
    Time it1 = asn1_to_utctime(X509_get_notBefore(issuer));
    Time it2 = asn1_to_utctime(X509_get_notAfter(issuer));
    if(pt1 < it1) pt1 = it1;
    if(pt2 > it2) pt2 = it2;
    ASN1_UTCTIME* not_before = utc_to_asn1time(pt1);
    ASN1_UTCTIME* not_after = utc_to_asn1time(pt2);
    if((!not_before) || (!not_after)) {
      if(not_before) ASN1_UTCTIME_free(not_before);
      if(not_after) ASN1_UTCTIME_free(not_after);
      return false;
    }
    X509_set_notBefore(tosign, not_before);
    X509_set_notAfter(tosign, not_after);
    ASN1_UTCTIME_free(not_before);
    ASN1_UTCTIME_free(not_after);
    return true;
  }
