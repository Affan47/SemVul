outputDevice() {
    if (!_outputDev) {
        GBool bitmapTopDown = gTrue;
        _outputDev = new SplashOutputDev(gSplashColorMode, 4, gFalse, gBgColor, bitmapTopDown);
        if (_outputDev)
            _outputDev->startDoc(_pdfDoc->getXRef());
    }
    return _outputDev;
}
