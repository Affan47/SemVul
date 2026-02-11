proc_init(kadm5_server_context *contextp,
	  krb5_storage *in,
	  krb5_storage *out)
{
    CHECK(krb5_store_uint32(out, VERSION2));
    CHECK(krb5_store_uint32(out, 0));
    CHECK(krb5_store_uint32(out, 0));
}
