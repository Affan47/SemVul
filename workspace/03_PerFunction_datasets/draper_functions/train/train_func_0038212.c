dsOpsTable_get_value(netsnmp_request_info *request,
                     netsnmp_index * item,
                     netsnmp_table_request_info *table_info)
{
    PRUint64 *the_stat = NULL;
    integer64 new_val;
    netsnmp_variable_list *var = request->requestvb;
    stats_table_context *context = (stats_table_context *) item;

    switch (table_info->colnum) {

    case COLUMN_DSANONYMOUSBINDS:
        the_stat = &context->ops_tbl.dsAnonymousBinds;
        break;

    case COLUMN_DSUNAUTHBINDS:
        the_stat = &context->ops_tbl.dsUnAuthBinds;
        break;

    case COLUMN_DSSIMPLEAUTHBINDS:
        the_stat = &context->ops_tbl.dsSimpleAuthBinds;
        break;

    case COLUMN_DSSTRONGAUTHBINDS:
        the_stat = &context->ops_tbl.dsStrongAuthBinds;
        break;

    case COLUMN_DSBINDSECURITYERRORS:
        the_stat = &context->ops_tbl.dsBindSecurityErrors;
        break;

    case COLUMN_DSINOPS:
        the_stat = &context->ops_tbl.dsInOps;
        break;

    case COLUMN_DSREADOPS:
        the_stat = &context->ops_tbl.dsReadOps;
        break;

    case COLUMN_DSCOMPAREOPS:
        the_stat = &context->ops_tbl.dsCompareOps;
        break;

    case COLUMN_DSADDENTRYOPS:
        the_stat = &context->ops_tbl.dsAddEntryOps;
        break;

    case COLUMN_DSREMOVEENTRYOPS:
        the_stat = &context->ops_tbl.dsRemoveEntryOps;
        break;

    case COLUMN_DSMODIFYENTRYOPS:
        the_stat = &context->ops_tbl.dsModifyEntryOps;
        break;

    case COLUMN_DSMODIFYRDNOPS:
        the_stat = &context->ops_tbl.dsModifyRDNOps;
        break;

    case COLUMN_DSLISTOPS:
        the_stat = &context->ops_tbl.dsListOps;
        break;

    case COLUMN_DSSEARCHOPS:
        the_stat = &context->ops_tbl.dsSearchOps;
        break;

    case COLUMN_DSONELEVELSEARCHOPS:
        the_stat = &context->ops_tbl.dsOneLevelSearchOps;
        break;

    case COLUMN_DSWHOLESUBTREESEARCHOPS:
        the_stat = &context->ops_tbl.dsWholeSubtreeSearchOps;
        break;

    case COLUMN_DSREFERRALS:
        the_stat = &context->ops_tbl.dsReferrals;
        break;

    case COLUMN_DSCHAININGS:
        the_stat = &context->ops_tbl.dsChainings;
        break;

    case COLUMN_DSSECURITYERRORS:
        the_stat = &context->ops_tbl.dsSecurityErrors;
        break;

    case COLUMN_DSERRORS:
        the_stat = &context->ops_tbl.dsErrors;
        break;

    case COLUMN_DSCONNECTIONS:
        the_stat = &context->ops_tbl.dsConnections;
        break;

    case COLUMN_DSCONNECTIONSINMAXTHREADS:
        the_stat = &context->ops_tbl.dsConnectionsInMaxThreads;
        break;

    case COLUMN_DSMAXTHREADSHIT:
        the_stat = &context->ops_tbl.dsMaxThreadsHit;
        break;

    default:
        snmp_log(LOG_ERR, "Unknown column in dsOpsTable_get_value\n");
        return SNMP_ERR_GENERR;
    }


    new_val.low = *the_stat & 0x00000000ffffffff;
    new_val.high =  (*the_stat >> 32) & 0x00000000ffffffff;

    snmp_set_var_typed_value(var, ASN_COUNTER64,
                                 (u_char *) &new_val,
                                 sizeof(new_val));

    return SNMP_ERR_NOERROR;
}
