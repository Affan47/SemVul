xmlSecGCryptKeyDataDsaInitialize(xmlSecKeyDataPtr data) {
    xmlSecAssert2(xmlSecKeyDataCheckId(data, xmlSecGCryptKeyDataDsaId), -1);

    return(xmlSecGCryptAsymKeyDataInitialize(data));
}
