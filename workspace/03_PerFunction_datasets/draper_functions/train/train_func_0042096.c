command_setformat(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	ret = do_command(gspca_dev, CPIA_COMMAND_SetFormat,
			 sd->params.format.videoSize,
			 sd->params.format.subSample,
			 sd->params.format.yuvOrder, 0);
	if (ret)
		return ret;

	return do_command(gspca_dev, CPIA_COMMAND_SetROI,
			  sd->params.roi.colStart, sd->params.roi.colEnd,
			  sd->params.roi.rowStart, sd->params.roi.rowEnd);
}
