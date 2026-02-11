performCurlTransaction(xmlrpc_env *      const envP,
                       curlTransaction * const curlTransactionP) {

    CURL * const curlSessionP = curlTransactionP->curlSessionP;

    CURLcode res;

    res = curl_easy_perform(curlSessionP);

    if (res != CURLE_OK)
        xmlrpc_env_set_fault_formatted(
            envP, XMLRPC_NETWORK_ERROR, "Curl failed to perform "
            "HTTP POST request.  curl_easy_perform() says: %s (%d)",
            curlTransactionP->curlError, res);
    else {
        CURLcode crRes;
        long http_result;
        crRes = curl_easy_getinfo(curlSessionP, CURLINFO_HTTP_CODE,
                                &http_result);

        if (crRes != CURLE_OK)
            xmlrpc_env_set_fault_formatted(
                envP, XMLRPC_INTERNAL_ERROR,
                "Curl performed the HTTP POST request, but was "
                "unable to say what the HTTP result code was.  "
                "curl_easy_getinfo(CURLINFO_HTTP_CODE) says: %s",
                curlTransactionP->curlError);
        else {
            if (http_result != 200)
                xmlrpc_env_set_fault_formatted(
                    envP, XMLRPC_NETWORK_ERROR, "HTTP response: %ld",
                    http_result);
        }
    }
}
