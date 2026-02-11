ToggleTab(int tab, bool show) {
    if (tab>=0 && tab<items_.count()) {
        items_[tab].enabled_=show;
        Mode m=mode_;
        mode_=Mode_None;
        SetMode(m);
        emit TabToggled(tab);
    }
}
