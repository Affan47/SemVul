ns1__mul(struct soap *soap, double a, double b, double *result)
{ const char *username = soap_wsse_get_Username(soap);
  if (username)
    fprintf(stderr, "Hello %s, want to multiply %g * %g = ?\n", username, a, b);
  if (soap_wsse_verify_Timestamp(soap)
   || soap_wsse_verify_Password(soap, "userPass"))
  { soap_wsse_delete_Security(soap);
    return soap->error;
  }
  if (soap_wsse_verify_element(soap, "http://www.genivia.com/schemas/wssetest.xsd", "mul") == 0)
  { soap_wsse_delete_Security(soap);
    return soap_sender_fault(soap, "Service operation not signed", NULL);
  }
  soap_wsse_delete_Security(soap);
  soap_wsse_add_Timestamp(soap, "Time", 10);


  if (hmac)
  { soap_wsse_sign_body(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));

    soap_wsse_add_SecurityContextToken(soap, "SCT", contextId);
  }
  else
  { if (nokey)
      soap_wsse_add_KeyInfo_KeyName(soap, "MyKey");
    else
    { soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert);
      soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token");
    }
    soap_wsse_sign_body(soap, SOAP_SMD_SIGN_RSA_SHA256, rsa_privk, 0);
  }
  *result = a * b;
  return SOAP_OK;
}
