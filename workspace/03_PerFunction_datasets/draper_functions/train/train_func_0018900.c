paint(Graphics &g, const YRect &) {
    int const w(width());
    int const h(height());

    g.setColor(taskBarBg);

#ifdef CONFIG_GRADIENTS
    ref<YImage> gradient(parent() ? parent()->getGradient() : null);

    if (gradient != null)
        g.drawImage(gradient, x(), y(), w, h, 0, 0);
    else
#endif
    if (taskbackPixmap != null)
        g.fillPixmap(taskbackPixmap, 0, 0, w, h, x(), y());
    else
        g.fillRect(0, 0, w, h);

    if (trayDrawBevel && w > 1) {
        if (wmLook == lookMetal)
            g.draw3DRect(1, 1, w - 2, h - 2, false);
        else
            g.draw3DRect(0, 0, w - 1, h - 1, false);
    }
}
