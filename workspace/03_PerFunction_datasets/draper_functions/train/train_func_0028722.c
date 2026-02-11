set_icon_name(ManagedWindowHintInfo& info) {
    if (info.style_ != nil) {
	Style& s = *info.style_;
	String v;
	if (s.find_attribute("iconName", v) || s.find_attribute("name", v)) {
	    NullTerminatedString ns(v);
	    XSetIconName(info.dpy_, info.xwindow_, ns.string());
	}
    }
    return false;
}
