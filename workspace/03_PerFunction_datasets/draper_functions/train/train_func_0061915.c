url_subbbscgi_new()
{
    if( CORE::get_loginp2()->login_now() ) return CONFIG::get_url_loginp2() + "post.php";

    return Board2chCompati::url_subbbscgi_new();
}
