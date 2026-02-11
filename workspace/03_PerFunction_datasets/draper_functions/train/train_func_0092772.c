svgNSOnly(QString svgContent) {
    svgContent.remove(Xmlns);
    int ix = svgContent.indexOf("<svg");
    if (ix >= 0) {
        svgContent.insert(ix + 5, "xmlns=\"http://www.w3.org/2000/svg\" ");
    }
    return svgContent;
}
