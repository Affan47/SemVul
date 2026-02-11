operator=(const subtitle &sub)
{
	if (this != &sub) {
		if (image_id != -1) {
			if ( bm_release(image_id) ) {
				image_id = -1;
			}
		}

		clone(sub);
	}

	return *this;
}
