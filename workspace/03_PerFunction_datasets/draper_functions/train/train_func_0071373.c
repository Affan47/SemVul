emit_token( const char *fc_name)
{

    if ( handle_tic_vocab( (char *)fc_name, fc_tokens_list_start) )
    {
        return;
    }

    tokenization_error( FATAL, "Did not recognize FCode name %s", fc_name);
}
