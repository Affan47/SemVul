test_folder_parser_normal (void)
{
	GDataDocumentsFolder *folder;
	gchar *path;
	GDataAuthor *author;
	GError *error = NULL;

	folder = GDATA_DOCUMENTS_FOLDER (gdata_parsable_new_from_xml (GDATA_TYPE_DOCUMENTS_FOLDER,
		"<?xml version='1.0' encoding='UTF-8'?>"
		"<entry xmlns='http://www.w3.org/2005/Atom' xmlns:docs='http://schemas.google.com/docs/2007' "
		       "xmlns:batch='http://schemas.google.com/gdata/batch' xmlns:gd='http://schemas.google.com/g/2005' "
		       "gd:etag='&quot;WBYEFh8LRCt7ImBk&quot;'>"
			"<id>https://docs.google.com/feeds/id/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams</id>"
			"<published>2012-04-14T09:12:19.418Z</published>"
			"<updated>2012-04-14T09:12:19.418Z</updated>"
			"<app:edited xmlns:app='http://www.w3.org/2007/app'>2012-04-14T09:12:20.055Z</app:edited>"
			"<category scheme='http://schemas.google.com/g/2005#kind' term='http://schemas.google.com/docs/2007#folder' label='folder'/>"
			"<title>Temporary Folder</title>"
			"<content type='application/atom+xml;type=feed' "
			         "src='https://docs.google.com/feeds/default/private/full/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams/contents'/>"
			"<link rel='alternate' type='text/html' href='https://docs.google.com/#folders/folder.0.0BzY2jgHHwMwYalFhbjhVT3dyams'/>"
			"<link rel='http://schemas.google.com/docs/2007#icon' type='image/png' href='https://ssl.gstatic.com/docs/doclist/images/icon_9_collection_list.png'/>"
			"<link rel='http://schemas.google.com/g/2005#resumable-create-media' type='application/atom+xml' href='https://docs.google.com/feeds/upload/create-session/default/private/full/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams/contents'/>"
			"<link rel='http://schemas.google.com/docs/2007#alt-post' type='application/atom+xml' href='https://docs.google.com/feeds/upload/file/default/private/full/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams/contents'/>"
			"<link rel='self' type='application/atom+xml' href='https://docs.google.com/feeds/default/private/full/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams'/>"
			"<link rel='edit' type='application/atom+xml' href='https://docs.google.com/feeds/default/private/full/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams'/>"
			"<author>"
				"<name>libgdata.documents</name>"
				"<email>libgdata.documents@gmail.com</email>"
			"</author>"
			"<gd:resourceId>folder:0BzY2jgHHwMwYalFhbjhVT3dyams</gd:resourceId>"
			"<gd:lastModifiedBy>"
				"<name>libgdata.documents</name>"
				"<email>libgdata.documents@gmail.com</email>"
			"</gd:lastModifiedBy>"
			"<gd:quotaBytesUsed>0</gd:quotaBytesUsed>"
			"<docs:writersCanInvite value='false'/>"
			"<gd:feedLink rel='http://schemas.google.com/acl/2007#accessControlList' href='https://docs.google.com/feeds/default/private/full/folder%3A0BzY2jgHHwMwYalFhbjhVT3dyams/acl'/>"
		"</entry>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_DOCUMENTS_FOLDER (folder));
	gdata_test_compare_kind (GDATA_ENTRY (folder), "http://schemas.google.com/docs/2007#folder", NULL);


	g_assert_cmpstr (gdata_documents_entry_get_resource_id (GDATA_DOCUMENTS_ENTRY (folder)), ==, "folder:0BzY2jgHHwMwYalFhbjhVT3dyams");

	path = gdata_documents_entry_get_path (GDATA_DOCUMENTS_ENTRY (folder));
	g_assert_cmpstr (path, ==, "/0BzY2jgHHwMwYalFhbjhVT3dyams");
	g_free (path);


	g_assert_cmpuint (gdata_documents_entry_get_edited (GDATA_DOCUMENTS_ENTRY (folder)), ==, 1334394740);
	g_assert_cmpuint (gdata_documents_entry_get_last_viewed (GDATA_DOCUMENTS_ENTRY (folder)), ==, -1);

	author = gdata_documents_entry_get_last_modified_by (GDATA_DOCUMENTS_ENTRY (folder));

	g_assert_cmpstr (gdata_author_get_name (author), ==, "libgdata.documents");
	g_assert_cmpstr (gdata_author_get_uri (author), ==, NULL);
	g_assert_cmpstr (gdata_author_get_email_address (author), ==, "libgdata.documents@gmail.com");


	g_assert (gdata_documents_entry_writers_can_invite (GDATA_DOCUMENTS_ENTRY (folder)) == FALSE);
	g_assert_cmpuint (gdata_documents_entry_get_quota_used (GDATA_DOCUMENTS_ENTRY (folder)), ==, 0);


	g_assert (gdata_documents_entry_is_deleted (GDATA_DOCUMENTS_ENTRY (folder)) == FALSE);

	g_object_unref (folder);
}
