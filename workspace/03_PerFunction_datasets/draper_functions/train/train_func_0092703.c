printGeom(const geom::Geometry *g)
{
	if ( HEXWKB_output )
	{
		std::stringstream s(std::ios_base::binary|std::ios_base::in|std::ios_base::out);
		wkbwriter->write(*g, s);
		std::stringstream s2;
		wkbreader->printHEX(s, s2);
		return s2.str();
	}
	else
	{
		return wktwriter->write(g);
	}
}
