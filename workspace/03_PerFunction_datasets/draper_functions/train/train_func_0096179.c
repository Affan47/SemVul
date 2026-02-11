init()
{
	for (int col = 0; col <= Color_ignore; ++col) {
		lcolors_[col] = QColor(lcolor.getX11Name(ColorCode(col)).c_str());
	}

	initialized_ = true;
}
