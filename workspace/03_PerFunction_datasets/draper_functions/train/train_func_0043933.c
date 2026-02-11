statistics()
{

    init();

    int size = 0;
    int msize = 0;
    int movie = 0;
    int images = 0;
    int scripts = 0;
    int stylesheets = 0;
    int sound = 0;
    int fonts = 0;
    foreach (CachedObject* o, *cache)
    {
        switch(o->type()) {
        case CachedObject::Image:
        {

            images++;


            break;
        }
        case CachedObject::CSSStyleSheet:
            stylesheets++;
            break;
        case CachedObject::Script:
            scripts++;
            break;
        case CachedObject::Sound:
            sound++;
            break;
        case CachedObject::Font:
            fonts++;
            break;
        }
        size += o->size();
    }
    size /= 1024;

    kDebug( 6060 ) << "------------------------- image cache statistics -------------------";
    kDebug( 6060 ) << "Number of items in cache:" << cache->count();
    kDebug( 6060 ) << "Number of cached images:" << images;
    kDebug( 6060 ) << "Number of cached movies:" << movie;
    kDebug( 6060 ) << "Number of cached scripts:" << scripts;
    kDebug( 6060 ) << "Number of cached stylesheets:" << stylesheets;
    kDebug( 6060 ) << "Number of cached sounds:" << sound;
    kDebug( 6060 ) << "Number of cached fonts:" << fonts;
    kDebug( 6060 ) << "pixmaps:   allocated space approx." << size << "kB";
    kDebug( 6060 ) << "movies :   allocated space approx." << msize/1024 << "kB";
    kDebug( 6060 ) << "--------------------------------------------------------------------";
}
