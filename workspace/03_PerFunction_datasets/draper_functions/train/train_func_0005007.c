load(upath filename) {
    ref<YImage> image;
    GError *gerror = 0;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cstring(filename.path()).c_str(), &gerror);

    if (pixbuf != NULL) {
        image.init(new YImageGDK(gdk_pixbuf_get_width(pixbuf),
                                 gdk_pixbuf_get_height(pixbuf),
                                 pixbuf));
    }
    return image;
}
