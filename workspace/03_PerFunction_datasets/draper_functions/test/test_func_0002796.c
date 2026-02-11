qt_pointsize(double ptsize)
{
	if (ptsize < 0.) ptsize = 1.;
	qt_out << GEPointSize << ptsize;
}
