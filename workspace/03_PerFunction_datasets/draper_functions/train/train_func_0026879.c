MsgAdd ( int a )
{
    if ( act_msg_len < (max_msg_len-1) )
        the_msg[ act_msg_len++ ] = ( unsigned char ) a;
}
