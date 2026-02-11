attachContextMenuItemInterface(as_object& o)
{
    const int flags = PropFlags::dontEnum |
                      PropFlags::dontDelete |
                      PropFlags::onlySWF7Up;

    Global_as& gl = getGlobal(o);
    o.init_member("copy", gl.createFunction(contextmenuitem_copy), flags);
}
