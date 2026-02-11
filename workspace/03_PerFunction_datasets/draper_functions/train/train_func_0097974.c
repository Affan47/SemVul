rectify_IPL(
	const void* srcImg_left,
	const void* srcImg_right,
	void* outImg_left,
	void* outImg_right) const
{
	MRPT_START
	ASSERT_(srcImg_left!=outImg_left && srcImg_right!=outImg_right)

	if (!isSet()) THROW_EXCEPTION("Error: setFromCamParams() must be called prior to rectify().")

#if MRPT_HAS_OPENCV && MRPT_OPENCV_VERSION_NUM>=0x200
	const uint32_t ncols = m_camera_params.leftCamera.ncols;
	const uint32_t nrows = m_camera_params.leftCamera.nrows;

	const uint32_t ncols_out = m_resize_output ? m_resize_output_value.x : ncols;
	const uint32_t nrows_out = m_resize_output ? m_resize_output_value.y : nrows;

	const CvMat mapx_left = cvMat(nrows_out,ncols_out,  CV_16SC2, const_cast<int16_t*>(&m_dat_mapx_left[0]) );
	const CvMat mapy_left = cvMat(nrows_out,ncols_out,  CV_16UC1, const_cast<uint16_t*>(&m_dat_mapy_left[0]) );
	const CvMat mapx_right = cvMat(nrows_out,ncols_out,  CV_16SC2, const_cast<int16_t*>(&m_dat_mapx_right[0]) );
	const CvMat mapy_right = cvMat(nrows_out,ncols_out,  CV_16UC1, const_cast<uint16_t*>(&m_dat_mapy_right[0]) );

	const cv::Mat mapx1 = cv::cvarrToMat(&mapx_left);
	const cv::Mat mapy1 = cv::cvarrToMat(&mapy_left);
	const cv::Mat mapx2 = cv::cvarrToMat(&mapx_right);
	const cv::Mat mapy2 = cv::cvarrToMat(&mapy_right);

	const cv::Mat src1 = cv::cvarrToMat(srcImg_left);
	const cv::Mat src2 = cv::cvarrToMat(srcImg_right);
	cv::Mat dst1 = cv::cvarrToMat(outImg_left);
	cv::Mat dst2 = cv::cvarrToMat(outImg_right);

    cv::remap( src1, dst1, mapx1, mapy1,static_cast<int>(m_interpolation_method),cv::BORDER_CONSTANT, cvScalarAll(0) );
    cv::remap( src2, dst2, mapx2, mapy2,static_cast<int>(m_interpolation_method),cv::BORDER_CONSTANT, cvScalarAll(0) );
#endif
	MRPT_END
}
