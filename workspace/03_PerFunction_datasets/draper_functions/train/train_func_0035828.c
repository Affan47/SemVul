xmlSecQName2BitMaskDebugDump(xmlSecQName2BitMaskInfoConstPtr info, xmlSecBitMask mask,
                            const xmlChar* name, FILE* output) {
    unsigned int ii;

    xmlSecAssert(info != NULL);
    xmlSecAssert(name != NULL);
    xmlSecAssert(output != NULL);

    if(mask == 0) {
        return;
    }

    fprintf(output, "== %s (0x%08x): ", name, mask);
    for(ii = 0; (mask != 0) && (info[ii].qnameLocalPart != NULL); ii++) {
        xmlSecAssert(info[ii].mask != 0);

        if((mask & info[ii].mask) != 0) {
            fprintf(output, "name=\"%s\" (href=\"%s\"),", info[ii].qnameLocalPart, info[ii].qnameHref);
        }
    }
    fprintf(output, "\n");
}
