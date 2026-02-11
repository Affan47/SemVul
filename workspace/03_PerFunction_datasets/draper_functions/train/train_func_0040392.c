setButtons(Qt::MouseButton hold, Qt::MouseButton thenPush)
{
    if (hold == thenPush) {
        d->m_hold = Qt::NoButton;
        d->m_thenPush = Qt::NoButton;
        return;
    }

    int button = hold;
    for (int i = 0; i < 2; i++) {
        switch (button) {
        case Qt::LeftButton:
        case Qt::RightButton:
        case Qt::MidButton:
        case Qt::XButton1:
        case Qt::XButton2:
            break;
        default:
            d->m_hold = Qt::NoButton;
            d->m_thenPush = Qt::NoButton;
            return;
        }
        button = thenPush;
    }

    d->m_hold = hold;
    d->m_thenPush = thenPush;
}
