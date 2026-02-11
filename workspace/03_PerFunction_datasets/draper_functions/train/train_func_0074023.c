setDragProperty(
    XDisplay* display, XEvent& xevent, XWindow destination,
    Atom messageType, int x, int y, const char* value = 0,
    int length = 0
) {
    Atom property = None;
    if (length != 0) {
	char buffer[256];
	std::ostrstream name(buffer, 256);
	name << dragName << "_" << Host::name() << "_" << getpid() << "_"  <<
	    dropUid++ << '\0';
	property = XInternAtom(display, name.str(), False);

	XChangeProperty(
	    display, destination, property, XA_STRING, 8,
	    PropModePrepend,
	    (unsigned char*)value + (length<0 ? length : 0),
	    Math::abs(length)
	);
    }

    xevent.xclient.type = ClientMessage;
    xevent.xclient.window = destination;
    xevent.xclient.display = display;
    xevent.xclient.message_type = messageType;
    xevent.xclient.format = 32;

    xevent.xclient.data.l[0] = x;
    xevent.xclient.data.l[1] = y;

    xevent.xclient.data.l[2] = destination;
    xevent.xclient.data.l[3] = property;
    xevent.xclient.data.l[4] = length;
}
