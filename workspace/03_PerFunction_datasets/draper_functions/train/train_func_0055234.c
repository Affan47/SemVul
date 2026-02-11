get_proxy_basicauth_w()
{
    if( CORE::get_loginp2()->login_now() ) return CONFIG::get_proxy_basicauth_for_data();

    const int mode = get_mode_local_proxy_w();

    if( mode == DBTREE::PROXY_GLOBAL ) return CONFIG::get_proxy_basicauth_for2ch_w();
    else if( mode == DBTREE::PROXY_LOCAL ) return get_local_proxy_basicauth_w();

    return std::string();
}
