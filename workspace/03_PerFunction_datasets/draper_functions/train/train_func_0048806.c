fix_up(REQUEST *request)
{
	VALUE_PAIR *vp;

	request->username = NULL;
	request->password = NULL;

	for (vp = request->packet->vps; vp != NULL; vp = vp->next) {
		if ((vp->attribute == PW_USER_NAME) &&
		    !request->username) {
			request->username = vp;

		} else if (vp->attribute == PW_STRIPPED_USER_NAME) {
			request->username = vp;

		} else if (vp->attribute == PW_USER_PASSWORD) {
			request->password = vp;
		}
	}
}
