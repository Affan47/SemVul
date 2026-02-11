test_parsing_app_control (void)
{
	GDataYouTubeVideo *video;
	GDataYouTubeState *state;
	GError *error = NULL;

	video = GDATA_YOUTUBE_VIDEO (gdata_parsable_new_from_xml (GDATA_TYPE_YOUTUBE_VIDEO,
		"<entry xmlns='http://www.w3.org/2005/Atom' "
			"xmlns:media='http://search.yahoo.com/mrss/' "
			"xmlns:yt='http://gdata.youtube.com/schemas/2007' "
			"xmlns:gd='http://schemas.google.com/g/2005' "
			"gd:etag='W/\"CEMFSX47eCp7ImA9WxVUGEw.\"'>"
			"<id>tag:youtube.com,2008:video:JAagedeKdcQ</id>"
			"<published>2006-05-16T14:06:37.000Z</published>"
			"<updated>2009-03-23T12:46:58.000Z</updated>"
			"<app:control xmlns:app='http://www.w3.org/2007/app'>"
				"<app:draft>yes</app:draft>"
				"<yt:state name='blacklisted'>This video is not available in your country</yt:state>"
			"</app:control>"
			"<category scheme='http://schemas.google.com/g/2005#kind' term='http://gdata.youtube.com/schemas/2007#video'/>"
			"<title>Judas Priest - Painkiller</title>"
			"<link rel='http://www.iana.org/assignments/relation/alternate' type='text/html' href='http://www.youtube.com/watch?v=JAagedeKdcQ'/>"
			"<link rel='http://www.iana.org/assignments/relation/self' type='application/atom+xml' href='http://gdata.youtube.com/feeds/api/videos/JAagedeKdcQ?client=ytapi-google-jsdemo'/>"
			"<author>"
				"<name>eluves</name>"
				"<uri>http://gdata.youtube.com/feeds/api/users/eluves</uri>"
			"</author>"
			"<media:group>"
				"<media:title type='plain'>Judas Priest - Painkiller</media:title>"
				"<media:credit role='uploader' scheme='urn:youtube'>eluves</media:credit>"
				"<media:category label='Music' scheme='http://gdata.youtube.com/schemas/2007/categories.cat'>Music</media:category>"
			"</media:group>"
		"</entry>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_YOUTUBE_VIDEO (video));
	g_clear_error (&error);


	g_assert (gdata_youtube_video_is_draft (video) == TRUE);

	state = gdata_youtube_video_get_state (video);
	g_assert_cmpstr (gdata_youtube_state_get_name (state), ==, "blacklisted");
	g_assert_cmpstr (gdata_youtube_state_get_message (state), ==, "This video is not available in your country");
	g_assert (gdata_youtube_state_get_reason_code (state) == NULL);
	g_assert (gdata_youtube_state_get_help_uri (state) == NULL);


	g_object_unref (video);
}
