ossl_ec_key_dh_compute_key(VALUE self, VALUE pubkey)
{
    EC_KEY *ec;
    EC_POINT *point;
    int buf_len;
    VALUE str;

    Require_EC_KEY(self, ec);
    SafeRequire_EC_POINT(pubkey, point);


    buf_len = 1024;
    str = rb_str_new(0, buf_len);

    buf_len = ECDH_compute_key(RSTRING_PTR(str), buf_len, point, ec, NULL);
    if (buf_len < 0)
         ossl_raise(eECError, "ECDH_compute_key");

    rb_str_resize(str, buf_len);

    return str;
}
