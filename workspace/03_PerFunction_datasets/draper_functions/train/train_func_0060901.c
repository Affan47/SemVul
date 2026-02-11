downloader_xfer_close ( struct xfer_interface *xfer, int rc ) {
	struct downloader *downloader =
		container_of ( xfer, struct downloader, xfer );


	if ( rc == 0 )
		rc = downloader->register_image ( downloader->image );


	downloader_finished ( downloader, rc );
}
