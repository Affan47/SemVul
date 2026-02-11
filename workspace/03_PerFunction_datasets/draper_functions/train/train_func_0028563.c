main(int argc, char **argv)
{ struct soap soap;
  char *body;
  if (argc < 2)
  { fprintf(stderr, "Usage: httpgettest URL\n");
    exit(0);
  }
  soap_init(&soap);
  soap_register_plugin(&soap, http_get);
  if (soap_get_connect(&soap, argv[1], NULL)
   || soap_begin_recv(&soap))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  if (soap.http_content)
    printf("HTTP Content Type: %s\n", soap.http_content);
  body = soap_get_http_body(&soap);
  soap_end_recv(&soap);
  if (body)
    printf("HTTP Body:\n%s\n", body);
  soap_end(&soap);
  soap_done(&soap);
  return 0;
}
