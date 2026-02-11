appParamsTruthValue_set(dessertAppParamsTable_rowreq_ctx * rowreq_ctx,
                        u_long appParamsTruthValue_val)
{

    DEBUGMSGTL(("verbose:dessertAppParamsTable:appParamsTruthValue_set",
                "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);


    switch (appParamsTruthValue_val) {
    case TRUTHVALUE_TRUE:
        rowreq_ctx->data.appParamsTruthValue =
            INTERNAL_DESSERTAPPPARAMSTABLE_APPPARAMSTRUTHVALUE_TRUE;
        break;

    case TRUTHVALUE_FALSE:
        rowreq_ctx->data.appParamsTruthValue =
            INTERNAL_DESSERTAPPPARAMSTABLE_APPPARAMSTRUTHVALUE_FALSE;
        break;

    default:
        snmp_log(LOG_ERR,
                 "couldn't reverse map value %ld for appParamsTruthValue\n",
                 appParamsTruthValue_val);
        return SNMP_ERR_GENERR;
    }


    return MFD_SUCCESS;
}
