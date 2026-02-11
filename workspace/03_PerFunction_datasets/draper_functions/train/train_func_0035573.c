startTag(const char* name) {
    if (inTag)
        endTag();
    char buf[256];
    snprintf(buf, 256, "<%s", name);
    writeTabbed(buf);
    openTags.push(name);
    inTag = true;
}
