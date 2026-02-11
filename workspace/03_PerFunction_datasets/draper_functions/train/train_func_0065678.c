free_DigestInit(DigestInit *data)
{
der_free_utf8string(&(data)->type);
if((data)->channel) {
der_free_utf8string(&((data)->channel)->cb_type);
der_free_utf8string(&((data)->channel)->cb_binding);
free((data)->channel);
(data)->channel = NULL;
}
if((data)->hostname) {
der_free_utf8string((data)->hostname);
free((data)->hostname);
(data)->hostname = NULL;
}
}
