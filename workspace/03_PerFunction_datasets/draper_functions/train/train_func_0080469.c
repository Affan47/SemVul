loadImage(const std::string &image_filename) {
    Display *disp = FbTk::App::instance()->display();

    Cache *cache_item = findCache(image_filename);
    if (cache_item != 0) {
        cache_item->m_count++;
        m_icon_pixmap = cache_item->m_pixmap;
        m_icon_mask = cache_item->m_mask;

        resize(cache_item->m_width, cache_item->m_height);
#ifdef HAVE_SHAPE
        XShapeCombineMask(disp, m_icon_window.window(),
                          ShapeBounding, 0, 0, cache_item->m_mask, ShapeSet);
#endif

        return true;
    }

    Pixmap pixmap, mask;
    unsigned int pm_width = 1, pm_height = 1;

    Window rootwindow = m_icon_window.window();


    std::auto_ptr<FbTk::PixmapWithMask> img(FbTk::Image::load(image_filename,
                                                              m_icon_window.screenNumber()));
    if (img.get() == 0) {
        XpmAttributes xpm_attr;
        xpm_attr.valuemask = 0;
        mask = 0;


        int retvalue = XpmCreatePixmapFromData(disp,
                                               rootwindow,
                                               default_xpm, &pixmap, &mask, &xpm_attr);

        cerr<<"Load pixmap failed! ("<<image_filename<<")"<<endl;
        cerr<<"Using default pixmap"<<endl;

        if (pixmap == None || retvalue != XpmSuccess)
            throw string("FbDesk::Icon: Can't load default pixmap!");

        pm_width = xpm_attr.width;
        pm_height = xpm_attr.height;

    } else {

        pm_width = img->pixmap().width();
        pm_height = img->pixmap().height();
        pixmap = img->pixmap().release();
        mask = img->mask().release();
    }


    Cache *new_cache_item = new Cache;
    new_cache_item->m_pixmap = pixmap;
    new_cache_item->m_mask = mask;
    new_cache_item->m_filename = image_filename;
    new_cache_item->m_count = 1;
    new_cache_item->m_width = pm_width;
    new_cache_item->m_height = pm_height;

    m_cachelist.push_back(new_cache_item);

    m_icon_pixmap = pixmap;
    m_icon_mask = mask;

    resize(pm_width, pm_height);

#ifdef HAVE_SHAPE
    XShapeCombineMask(m_icon_window.display(), m_icon_window.window(),
                      ShapeBounding, 0, 0, mask, ShapeSet);
#endif

    return true;
}
