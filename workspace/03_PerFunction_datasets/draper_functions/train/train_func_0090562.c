paint(Graphics &g, const YRect &) {
    if (fInternal)
        return;
#ifdef CONFIG_TASKBAR
    if (taskBarBg)
        g.setColor(taskBarBg);
#endif
    g.fillRect(0, 0, width(), height());
    if (trayDrawBevel && fDocked.getCount())
        g.draw3DRect(0, 0, width() - 1, height() - 1, false);
}
