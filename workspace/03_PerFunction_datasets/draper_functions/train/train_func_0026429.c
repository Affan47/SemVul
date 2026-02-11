GenPOI(JarchSession *session)
{
	ImageDVDCombo idc;
	KeyStorage poi;
	LargeSplitImage dvd;
	RippedMap map;

	if (session->todo->get(TODO_GENPOI) && !session->force_genpoi)
		return;

	ReadDVDCapacity(session);
	if (session->DVD_capacity == 0)
		return;

	if (poi.open("JarchDVD-POI.keystore") < 0)
		return;
	if (dvd.open("dvdrom-image") < 0)
		return;
	if (map.open("dvdrom-image.ripmap") < 0)
		return;

	idc.map = &map;
	idc.dvd = &dvd;
	idc.poi = &poi;

	GenPOI_Dumb(session,&idc);
	GenPOI_Gaps(session,&idc);
	GenPOI_DVDVideo(session,&idc);

	if (	session->todo->get(TODO_GENPOI_DUMB) &&
		session->todo->get(TODO_GENPOI_DVDVIDEO)) {
		session->todo->set(TODO_GENPOI,1);
	}
}
