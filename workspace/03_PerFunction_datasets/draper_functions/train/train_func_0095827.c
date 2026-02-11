Close()
{
#if MRPT_HAS_FTDI
	ftdi_context *ctx = static_cast<ftdi_context *>(m_ftdi_context);
	if (ctx->usb_dev)
	{
		ftdi_usb_close( ctx );
		ctx->usb_dev = NULL;
	}


	ftdi_deinit( ctx );
	ftdi_init( ctx );

	m_readBuffer.clear();
#endif
}
