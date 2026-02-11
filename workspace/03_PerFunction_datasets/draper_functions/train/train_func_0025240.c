setColormap(Colormap cmap) {
    fColormap = cmap;
    if (getFrame() && manager->colormapWindow() == getFrame())
        manager->installColormap(cmap);
}
