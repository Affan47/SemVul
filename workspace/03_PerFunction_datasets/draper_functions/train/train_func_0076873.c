getRectifiedLeftImageParams() const
{
	if (!isSet()) THROW_EXCEPTION("Error: setFromCamParams() must be called before.")
	return m_rectified_image_params.leftCamera;
}
