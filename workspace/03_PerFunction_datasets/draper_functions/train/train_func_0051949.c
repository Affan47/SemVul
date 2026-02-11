check_utf8_string_san(hx509_validate_ctx ctx, heim_any *a)
{
    PKIXXmppAddr jid;
    size_t size;
    int ret;

    ret = decode_PKIXXmppAddr(a->data, a->length, &jid, &size);
    if (ret) {
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Decoding JID in SAN failed: %d", ret);
	return 1;
    }

    validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "%s", jid);
    free_PKIXXmppAddr(&jid);

    return 0;
}
