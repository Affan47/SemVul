asn1_append_tag(x509_node *node, int tag)
{
    int tl = 2;

    x509_node tmp;
    x509write_init_node(&tmp);

    if (tag == ASN1_BIT_STRING)
        ++tl;

    if (node->len > 127)
        x509write_realloc_node(&tmp, node->len + (size_t) tl +
            asn1_eval_octet((unsigned int)node->len));
    else
        x509write_realloc_node(&tmp, node->len + (size_t) tl);

    if (tmp.data == NULL) {
        x509write_free_node(&tmp);
        return 1;
    }


    *(tmp.p) = tag & 0xFF;
    ++tmp.p;


    if (tag == ASN1_BIT_STRING) {
        asn1_add_len((unsigned int) node->len + 1, &tmp);
        *(tmp.p) = 0x00;
        ++tmp.p;
    } else {
        asn1_add_len((unsigned int) node->len, &tmp);
    }


    memcpy(tmp.p, node->data, node->len);


    if ((tmp.p += (int) node->len -1) != tmp.end) {
        x509write_free_node(&tmp);
        return POLARSSL_ERR_X509_POINT_ERROR;
    }

    free(node->data);
    node->data = tmp.data;
    node->p = tmp.p;
    node->end = tmp.end;
    node->len = tmp.len;

    return 0;
}
