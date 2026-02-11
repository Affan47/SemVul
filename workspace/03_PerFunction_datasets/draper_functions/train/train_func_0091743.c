getPixmap(const FbTk::ThemeProxy<WinButtonTheme> &theme) const {
    switch(m_type) {
    case MAXIMIZE:
        return theme->maximizePixmap().pixmap().drawable();
    case MINIMIZE:
        return theme->iconifyPixmap().pixmap().drawable();
    case STICK:
        if (m_listen_to.isStuck())
            return theme->stuckPixmap().pixmap().drawable();
        else
            return theme->stickPixmap().pixmap().drawable();
    case CLOSE:
        return theme->closePixmap().pixmap().drawable();
    case SHADE:
        if (m_listen_to.isShaded())
            return theme->unshadePixmap().pixmap().drawable();
        else
            return theme->shadePixmap().pixmap().drawable();
    case MENUICON:
        if (m_icon_pixmap.drawable())
            return theme->titlePixmap().pixmap().drawable();
        else
            return theme->menuiconPixmap().pixmap().drawable();
    case LEFT_HALF:
        return theme->leftHalfPixmap().pixmap().drawable();
    case RIGHT_HALF:
        return theme->rightHalfPixmap().pixmap().drawable();
    default:
        return None;
    }
}
