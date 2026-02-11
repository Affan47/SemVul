soap_fault(struct soap *soap)
{
    if (!soap->fault)
    {   soap->fault = soap_new_SOAP_ENV__Fault(soap, -1);
        soap_default_SOAP_ENV__Fault(soap, soap->fault);
    }
    if (soap->version == 2 && !soap->fault->SOAP_ENV__Code)
    {   soap->fault->SOAP_ENV__Code = soap_new_SOAP_ENV__Code(soap, -1);
        soap_default_SOAP_ENV__Code(soap, soap->fault->SOAP_ENV__Code);
    }
    if (soap->version == 2 && !soap->fault->SOAP_ENV__Reason)
    {   soap->fault->SOAP_ENV__Reason = soap_new_SOAP_ENV__Reason(soap, -1);
        soap_default_SOAP_ENV__Reason(soap, soap->fault->SOAP_ENV__Reason);
    }
}
