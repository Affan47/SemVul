CheckAlgo(int first, int second, int* id, int* version)
{
    *id      = ALGO_ID_E;
    *version = PKCS5;

    if (first == 1) {
        switch (second) {
        case 1:
            *id = PBE_SHA1_RC4_128;
            *version = PKCS12;
            return 0;
        case 3:
            *id = PBE_SHA1_DES3;
            *version = PKCS12;
            return 0;
        default:
            return ALGO_ID_E;
        }
    }

    if (first != PKCS5)
        return ASN_INPUT_E;

    if (second == PBES2) {
        *version = PKCS5v2;
        return 0;
    }

    switch (second) {
    case 3:
        *id = PBE_MD5_DES;
        return 0;
    case 10:
        *id = PBE_SHA1_DES;
        return 0;
    default:
        return ALGO_ID_E;

    }
}
