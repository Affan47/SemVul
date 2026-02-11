cancel() {
    if (isUp) {
        cancelPopup();
        isUp = false;
    }
    if (fLastWindow) {
        displayFocus(fLastWindow);
    } else if (fActiveWindow) {
        fRoot->activate(fActiveWindow, false, true);
    }
    freeZList();
    fLastWindow = fActiveWindow = 0;
}
