Update () {
    int value;
    _state->GetValue(value);

    if (value == '\r') {
        UpdateCurClass();
        UpdateParentBrowser();
        UpdateChildBrowser();

    } else if (value == '\t' || value == '\033') {
        SelectCurClass();
        _focus = _curClass;

    } else if (value == '\007') {
        Complain();
    }

    if (value != QUIT_CODE) {
        UnselectBrowsers();
        _state->SetValue('\0');
    }
}
