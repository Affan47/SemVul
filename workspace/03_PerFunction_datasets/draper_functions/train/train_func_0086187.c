isFocused() const {
    return (fbwindow() ?
        fbwindow()->isFocused() && &fbwindow()->winClient() == this :
        false);
}
