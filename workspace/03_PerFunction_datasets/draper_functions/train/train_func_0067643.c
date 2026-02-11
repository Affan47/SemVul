getCharCatName(UChar32 cp) {
    uint8_t cat = getCharCat(cp);


    if (cat >= LENGTHOF(charCatNames)) {
        return "unknown";
    } else {
        return charCatNames[cat];
    }
}
