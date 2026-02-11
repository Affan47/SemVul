Write(ostream & os, Buffer const & buffer) const
{

	if (!filename.empty())
		os << "\tfilename " << filename.outputFileName(buffer.filePath()) << '\n';
	if (lyxscale != 100)
		os << "\tlyxscale " << lyxscale << '\n';
	if (!display)
		os << "\tdisplay false\n";
	if (!scale.empty() && !float_equal(convert<double>(scale), 0.0, 0.05)) {
		if (!float_equal(convert<double>(scale), 100.0, 0.05))
			os << "\tscale " << scale << '\n';
	} else {
		if (!width.zero())
			os << "\twidth " << width.asString() << '\n';
		if (!height.zero())
			os << "\theight " << height.asString() << '\n';
	}

	if (keepAspectRatio)
		os << "\tkeepAspectRatio\n";
	if (draft)
		os << "\tdraft\n";
	if (noUnzip)
		os << "\tnoUnzip\n";
	if (scaleBeforeRotation)
		os << "\tscaleBeforeRotation\n";

	if (!bb.empty())
		os << "\tBoundingBox " << bb << '\n';
	if (clip)
		os << "\tclip\n";

	if (!rotateAngle.empty()
		&& !float_equal(convert<double>(rotateAngle), 0.0, 0.001))
		os << "\trotateAngle " << rotateAngle << '\n';
	if (!rotateOrigin.empty())
		os << "\trotateOrigin " << rotateOrigin << '\n';
	if (!special.empty())
		os << "\tspecial " << special << '\n';
	if (!groupId.empty())
		os << "\tgroupId "<< groupId << '\n';
}
