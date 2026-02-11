parentOrderChanged(Focusable *win) {
    if(!m_screen.isShuttingdown() && contains(*win)) {
        if(insertFromParent(*win))
            m_ordersig.emit(win);
    }
}
