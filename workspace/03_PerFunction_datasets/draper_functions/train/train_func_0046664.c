got_select(FDSET_GROUP&, double timeout) {
    int iNumMsg;
    HTTP_OP* hop = NULL;
    CURLMsg *pcurlMsg = NULL;

    int iRunning = 0;
    CURLMcode curlMErr;


    while (1) {
        curlMErr = curl_multi_perform(g_curlMulti, &iRunning);
        if (curlMErr != CURLM_CALL_MULTI_PERFORM) break;
        if (dtime() - gstate.now > timeout) break;
    }


    while (1) {
        pcurlMsg = curl_multi_info_read(g_curlMulti, &iNumMsg);
        if (!pcurlMsg) break;


        hop = lookup_curl(pcurlMsg->easy_handle);
        if (!hop) continue;
        hop->handle_messages(pcurlMsg);
    }
}
