soap_serve_ns1__executeCommand(struct soap *soap)
{   struct ns1__executeCommand soap_tmp_ns1__executeCommand;
    struct ns1__executeCommandResponse soap_tmp_ns1__executeCommandResponse;
    char * soap_tmp_string;
    soap_default_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse);
    soap_tmp_string = NULL;
    soap_tmp_ns1__executeCommandResponse.result = &soap_tmp_string;
    soap_default_ns1__executeCommand(soap, &soap_tmp_ns1__executeCommand);
    soap->encodingStyle = NULL;
    if (!soap_get_ns1__executeCommand(soap, &soap_tmp_ns1__executeCommand, "ns1:executeCommand", NULL))
        return soap->error;
    if (soap_body_end_in(soap)
     || soap_envelope_end_in(soap)
     || soap_end_recv(soap))
        return soap->error;
    soap->error = ns1__executeCommand(soap, soap_tmp_ns1__executeCommand.command, &soap_tmp_string);
    if (soap->error)
        return soap->error;
    soap_serializeheader(soap);
    soap_serialize_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {   if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse, "ns1:executeCommandResponse", "")
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    };
    if (soap_end_count(soap)
     || soap_response(soap, SOAP_OK)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put_ns1__executeCommandResponse(soap, &soap_tmp_ns1__executeCommandResponse, "ns1:executeCommandResponse", "")
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap->error;
    return soap_closesock(soap);
}
