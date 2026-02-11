ssl_ext_list(apr_pool_t *p, conn_rec *c, int peer,
                                 const char *extension)
{
    SSLConnRec *sslconn = myConnConfig(c);
    SSL *ssl = NULL;
    apr_array_header_t *array = NULL;
    X509 *xs = NULL;
    ASN1_OBJECT *oid = NULL;
    int count = 0, j;

    if (!sslconn || !sslconn->ssl || !extension) {
        return NULL;
    }
    ssl = sslconn->ssl;


    oid = OBJ_txt2obj(extension, 0);
    if (!oid) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01970)
                      "could not parse OID '%s'", extension);
        ERR_clear_error();
        return NULL;
    }

    xs = peer ? SSL_get_peer_certificate(ssl) : SSL_get_certificate(ssl);
    if (xs == NULL) {
        return NULL;
    }

    count = X509_get_ext_count(xs);


    array = apr_array_make(p, count, sizeof(char *));
    for (j = 0; j < count; j++) {
        X509_EXTENSION *ext = X509_get_ext(xs, j);

        if (OBJ_cmp(ext->object, oid) == 0) {
            BIO *bio = BIO_new(BIO_s_mem());


            if (X509V3_EXT_print(bio, ext, 0, 0) == 1 ||
                dump_extn_value(bio, X509_EXTENSION_get_data(ext)) == 1) {
                BUF_MEM *buf;
                char **ptr = apr_array_push(array);
                BIO_get_mem_ptr(bio, &buf);
                *ptr = apr_pstrmemdup(p, buf->data, buf->length);
            } else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01971)
                              "Found an extension '%s', but failed to "
                              "create a string from it", extension);
            }
            BIO_vfree(bio);
        }
    }

    if (array->nelts == 0)
        array = NULL;

    if (peer) {

        X509_free(xs);
    }

    ASN1_OBJECT_free(oid);
    ERR_clear_error();
    return array;
}
