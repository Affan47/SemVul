send ( int nframes, float * val, int chan ) const
{
	std::stringstream dst;
	dst << dest() << chan;
	oscout << OSCStart(dst.str().c_str());
	for (int n=0; n<nframes; n++)
		oscout << val[n];
	oscout << OSCEnd();
}


}
