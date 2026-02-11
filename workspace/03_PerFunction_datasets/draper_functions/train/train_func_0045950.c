get_link_icon(char linkStatus, int sameNation)
{
	char  goodLinkName[9] = "LINK_EE1";
	goodLinkName[7] = '1'+ (char) (sys.frame_count/2%3);

	switch( linkStatus )
	{
		case LINK_EE:
			return image_icon.get_ptr(goodLinkName);

		case LINK_ED:
			return image_icon.get_ptr("LINK_ED");

		case LINK_DE:
			return image_icon.get_ptr("LINK_DE");

		case LINK_DD:
			if( sameNation )
				return image_icon.get_ptr("LINK_DE");
			else
				return image_icon.get_ptr("LINK_DD");
	}

	err_here();

	return NULL;
}
