xmlSchemaIDCStoreKey(xmlSchemaValidCtxtPtr vctxt,
                     xmlSchemaPSVIIDCKeyPtr key)
{


    if (vctxt->idcKeys == NULL) {
        vctxt->idcKeys = (xmlSchemaPSVIIDCKeyPtr *)
            xmlMalloc(40 * sizeof(xmlSchemaPSVIIDCKeyPtr));
        if (vctxt->idcKeys == NULL) {
            xmlSchemaVErrMemory(vctxt,
                "allocating the IDC key storage list", NULL);
            return (-1);
        }
        vctxt->sizeIdcKeys = 40;
    } else if (vctxt->sizeIdcKeys <= vctxt->nbIdcKeys) {
        vctxt->sizeIdcKeys *= 2;
        vctxt->idcKeys = (xmlSchemaPSVIIDCKeyPtr *)
            xmlRealloc(vctxt->idcKeys, vctxt->sizeIdcKeys *
            sizeof(xmlSchemaPSVIIDCKeyPtr));
        if (vctxt->idcKeys == NULL) {
            xmlSchemaVErrMemory(vctxt,
                "re-allocating the IDC key storage list", NULL);
            return (-1);
        }
    }
    vctxt->idcKeys[vctxt->nbIdcKeys++] = key;

    return (0);
}
