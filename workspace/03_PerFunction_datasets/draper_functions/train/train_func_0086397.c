z_picture_data (void)
{
    zword pic = zargs[0];
    zword table = zargs[1];

    int height, width;
    int i;

    bool avail = os_picture_data (pic, &height, &width);

    for (i = 0; mapper[i].story_id != UNKNOWN; i++)

	if (story_id == mapper[i].story_id) {

	    if (pic == mapper[i].pic) {

		int height2, width2;

		avail &= os_picture_data (mapper[i].pic1, &height2, &width2);
		avail &= os_picture_data (mapper[i].pic2, &height2, &width2);

		height += height2;

	    } else if (pic == mapper[i].pic1 || pic == mapper[i].pic2)

		avail = FALSE;
	}

    storew ((zword) (table + 0), (zword) (height));
    storew ((zword) (table + 2), (zword) (width));

    branch (avail);

}
