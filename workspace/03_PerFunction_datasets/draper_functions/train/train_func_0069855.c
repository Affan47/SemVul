set_grouping( struct stat_context *ctx, char *modifier )
{
        int rv = 0;

        TRACE( "Doing grouping, modifier |%s| \n", modifier );
        if ( strcmp( modifier, "ip" ) == 0 ) {
                DBG( "Grouping POLICY_REMOTE | POLICY_ADDR \n" );
                ctx->common_policy = POLICY_REMOTE | POLICY_ADDR;
        } else if ( strcmp( modifier, "port" ) == 0 ) {
                DBG( "Grouping POLICY_REMOTE | POLICY_PORT \n" );
                ctx->common_policy = POLICY_REMOTE | POLICY_PORT;
        } else if ( strcmp( modifier, "state" ) == 0 ) {
                DBG( "Grouping POLICY_STATE\n" );
                ctx->common_policy = POLICY_STATE;
        } else if ( strcmp( modifier, "cloud" ) == 0 ) {
                DBG("Grouping POLICY_CLOUD\n");
                ctx->common_policy = POLICY_CLOUD | POLICY_REMOTE | POLICY_ADDR;
        } else if ( strcmp( modifier, "cloudp" ) == 0 ) {
                DBG("Grouping POLICY_CLOUD (port)\n");
                ctx->common_policy = POLICY_CLOUD | POLICY_REMOTE | POLICY_PORT;
        } else if ( strcmp( modifier, "if" ) == 0 ) {
                ctx->common_policy = POLICY_IF;
        } else {
                ERROR("Unkonwn grouping %s! \n", modifier );
                rv = -1;
        }

        return rv;
}
