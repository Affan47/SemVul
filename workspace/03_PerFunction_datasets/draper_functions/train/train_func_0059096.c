expirestr_from_sk( PKT_secret_key *sk )
{
    static char buffer[11+5];
    time_t atime;

    if( !sk->expiredate )
	return _("never     ");
    atime = sk->expiredate;
    return mk_datestr (buffer, atime);
}
