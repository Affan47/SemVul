setExtraStyleSheet(const QString &extraCss)
{
    d_qble->_extraCss = extraCss;
    if (d_qble->_extraCss.contains("{")) {
        int b = d_qble->_extraCss.indexOf("{") + 1;
        int e = d_qble->_extraCss.indexOf("}", b);
        if (e>0) {
            d_qble->_extraCss = d_qble->_extraCss.mid(b, e-b);
        } else {
            LOG_ERROR("Wrong styleSheet -> {} " + extraCss);
            d_qble->_extraCss.clear();
        }
    }
    d_qble->setSpecificStyleSheet();
}
