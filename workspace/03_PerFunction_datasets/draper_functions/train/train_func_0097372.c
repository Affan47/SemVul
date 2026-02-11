ConversionXYNotifyProc(w, event, args, num_args)
Widget w;
XEvent *event;
String *args;
Cardinal *num_args;
{
    KinputProtocolWidget kpw = (KinputProtocolWidget)w;
    XClientMessageEvent	*ev = &event->xclient;
    Window reqwin;
    ConvClient	*ccp;
    JinputData *jdp;

    TRACE(("ConversionXYNotifyProc(window=0x%lx)\n", ev->data.l[2]));

    if (!isCorrectClientEvent(kpw, event)) {

	DPRINT(("got invalid clientmessage event.\n"));
	return;
    }
    if (ev->data.l[1] != JINPUT_PROTOCOL_VERSION) {

	DPRINT(("ConversionXYNotifyProc(): unknown version number (0x%lx)\n", ev->data.l[1]));
	return;
    }
    reqwin = ev->data.l[2];
    if ((ccp = findClient(kpw, reqwin)) == NULL) {

	DPRINT(("got conversion end request from unknown window\n"));
	return;
    }
    if (ccp->protocol != jinput_protocol) {
	DPRINT(("got jinput-specific event from a client that use other protocol\n"));
	return;
    }
    jdp = (JinputData *)ccp->data;
    jdp->rawspotx = ev->data.l[3];
    jdp->rawspoty = ev->data.l[4];

    ccp->attrmask |= CASpotLocation;
    ccp->attrs.spotx = jdp->rawspotx;
    ccp->attrs.spoty = jdp->rawspoty +
      ((ccp->attrmask & CAFonts) ? ccp->attrs.fonts[0]->ascent : 0);

    if (ccp->conversion != NULL) {
	myChangeAttributes(ccp->conversion, CASpotLocation, &ccp->attrs);
    }
}
