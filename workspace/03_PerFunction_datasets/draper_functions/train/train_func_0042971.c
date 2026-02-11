qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Config *_t = static_cast<Config *>(_o);
        switch (_id) {
        case 0: _t->configChanged(); break;
        case 1: _t->wallpaperChanged(); break;
        case 2: _t->photoChanged(); break;
        case 3: _t->widgetAdded(); break;
        case 4: _t->layerChange(); break;
        case 5: _t->proxyChanged(); break;
        case 6: _t->proxyPortChanged(); break;
        case 7: _t->proxyURLChanged(); break;
        case 8: _t->proxyUserChanged(); break;
        case 9: _t->proxyPasswdChanged(); break;
        case 10: _t->widgetListChanged(); break;
        case 11: _t->themepackNameChanged(); break;
        case 12: _t->iconThemechanged(); break;
        case 13: _t->openGLChanged(); break;
        case 14: _t->setWallpaper((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->setWallpaperMode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->setPhoto((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->addWidget((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->changeLayer(); break;
        default: ;
        }
    }
}
