GetCertFieldItems(const CKYByte *dercert,unsigned int cert_length,
        CCItem *issuer, CCItem *serial, CCItem *derSN, CCItem *subject,
        CCItem *valid, CCItem *subjkey)
{
    const CKYByte *buf;
    unsigned int buf_length;
    const CKYByte*dummy;
    unsigned int dummylen;


    buf = dataStart(dercert,cert_length,&buf_length, false);
    if (buf == NULL) return SECFailure;


    buf = dataStart(buf,buf_length,&buf_length,false);
    if (buf == NULL) return SECFailure;


    if ((buf[0] & 0xa0) == 0xa0) {
        dummy = dataStart(buf,buf_length,&dummylen,false);
        if (dummy == NULL) return SECFailure;
        buf_length -= (dummy-buf) + dummylen;
        buf = dummy + dummylen;
    }


    if (derSN) {
        derSN->data=dataStart(buf,buf_length,&derSN->len,true);
    }
    serial->data = dataStart(buf,buf_length,&serial->len,false);
    if (serial->data == NULL) return SECFailure;
    buf_length -= (serial->data-buf) + serial->len;
    buf = serial->data + serial->len;


    dummy = dataStart(buf,buf_length,&dummylen,false);
    if (dummy == NULL) return SECFailure;
    buf_length -= (dummy-buf) + dummylen;
    buf = dummy + dummylen;


    issuer->data = dataStart(buf,buf_length,&issuer->len,true);
    if (issuer->data == NULL) return SECFailure;
    buf_length -= (issuer->data-buf) + issuer->len;
    buf = issuer->data + issuer->len;


    valid->data = dataStart(buf,buf_length,&valid->len,false);
    if (valid->data == NULL) return SECFailure;
    buf_length -= (valid->data-buf) + valid->len;
    buf = valid->data + valid->len;


    subject->data=dataStart(buf,buf_length,&subject->len,true);
    if (subject->data == NULL) return SECFailure;
    buf_length -= (subject->data-buf) + subject->len;
    buf = subject->data + subject->len;


    subjkey->data=dataStart(buf,buf_length,&subjkey->len,false);
    if (subjkey->data == NULL) return SECFailure;
    buf_length -= (subjkey->data-buf) + subjkey->len;
    buf = subjkey->data + subjkey->len;
    return SECSuccess;
}
