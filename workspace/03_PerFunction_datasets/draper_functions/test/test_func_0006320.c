textProperty(Atom property) const {
    XTextProperty text_prop;
    char ** stringlist;
    int count;
    std::string ret;

    if (XGetTextProperty(display(), window(), &text_prop, property) == 0)
        return "";

    if (text_prop.value == 0 || text_prop.nitems == 0)
        return "";

    if (text_prop.encoding != XA_STRING) {

        if (XmbTextPropertyToTextList(display(), &text_prop, &stringlist, &count) == 0 || count == 0)
            return "";
    } else {
        if (XTextPropertyToStringList(&text_prop, &stringlist, &count) == 0 || count == 0)
            return "";

    }

    ret = stringlist[0];
    XFreeStringList(stringlist);
    return ret;
}
