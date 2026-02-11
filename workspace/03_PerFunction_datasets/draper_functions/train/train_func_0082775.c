call_info_free(call_info * const callInfoP) {


    XMLRPC_ASSERT_PTR_OK(callInfoP);


    if (callInfoP->_asynch_data_holder)
        xmlrpc_DECREF(callInfoP->_asynch_data_holder);


    if (callInfoP->serialized_xml)
         xmlrpc_mem_block_free(callInfoP->serialized_xml);

    free(callInfoP);
}
