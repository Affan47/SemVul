printContainer(struct SResource *res, const char *container, const char *restype, const char *mimetype, const char *id, UErrorCode *status)
{
    char resKeyBuffer[8];
    const char *resname = NULL;
    char *sid = NULL;

    write_tabs(out);

    resname = res_getKeyString(srBundle, res, resKeyBuffer);
    if (resname != NULL && *resname != 0) {
        sid = getID(id, resname, sid);
    } else {
        sid = getID(id, NULL, sid);
    }

    write_utf8_file(out, UnicodeString("<"));
    write_utf8_file(out, UnicodeString(container));
    printAttribute("id", sid, (int32_t) uprv_strlen(sid));

    if (resname != NULL) {
        printAttribute("resname", resname, (int32_t) uprv_strlen(resname));
    }

    if (mimetype != NULL) {
        printAttribute("mime-type", mimetype, (int32_t) uprv_strlen(mimetype));
    }

    if (restype != NULL) {
        printAttribute("restype", restype, (int32_t) uprv_strlen(restype));
    }

    tabCount += 1;
    if (res->fComment.fLength > 0) {

        printComments(&res->fComment, resname, TRUE, status);
    } else {
        write_utf8_file(out, UnicodeString(">\n"));
    }

    return sid;
}
