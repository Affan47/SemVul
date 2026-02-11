ARTchecksize(CHANNEL *cp)
{
    size_t size;
    HDRCONTENT *hc = cp->Data.HdrContent;
    const char *msgid;

    size = cp->Next - cp->Start;
    if (innconf->maxartsize != 0 && size > innconf->maxartsize) {
        if (cp->State == CSgotarticle || cp->State == CSgotlargearticle)
            cp->State = CSgotlargearticle;
        else
            cp->State = CSeatarticle;
    }
    if (cp->State == CSgotlargearticle) {
        notice("%s internal rejecting huge article (%lu > %lu)", CHANname(cp),
               (unsigned long) size, innconf->maxartsize);
        ARTerror(cp, "Article of %lu bytes exceeds local limit of %lu bytes",
                 (unsigned long) size, innconf->maxartsize);


	if (HDR_FOUND(HDR__MESSAGE_ID)) {
            HDR_LASTCHAR_SAVE(HDR__MESSAGE_ID);
            HDR_PARSE_START(HDR__MESSAGE_ID);
            msgid = HDR(HDR__MESSAGE_ID);


            if (!HIScheck(History, msgid) && !InndHisRemember(msgid, 0))
                warn("SERVER cant write %s", msgid);
            HDR_PARSE_END(HDR__MESSAGE_ID);
	}
    }
}
