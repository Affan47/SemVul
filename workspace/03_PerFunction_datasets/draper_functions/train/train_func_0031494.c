replaceLabel(UnicodeString &dest, int32_t destLabelStart, int32_t destLabelLength,
             const UnicodeString &label, int32_t labelLength) {
    if(&label!=&dest) {
        dest.replace(destLabelStart, destLabelLength, label);
    }
    return labelLength;
}
