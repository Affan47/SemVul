xmlSecGCryptKeyDataDesSet(xmlSecKeyDataPtr data, const xmlSecByte* buf, xmlSecSize bufSize) {
    xmlSecBufferPtr buffer;

    xmlSecAssert2(xmlSecKeyDataCheckId(data, xmlSecGCryptKeyDataDesId), -1);
    xmlSecAssert2(buf != NULL, -1);
    xmlSecAssert2(bufSize > 0, -1);

    buffer = xmlSecKeyDataBinaryValueGetBuffer(data);
    xmlSecAssert2(buffer != NULL, -1);

    return(xmlSecBufferSetData(buffer, buf, bufSize));
}
