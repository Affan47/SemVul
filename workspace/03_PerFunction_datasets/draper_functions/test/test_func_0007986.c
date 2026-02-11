generateRandomMaskImage(mrpt::math::CMatrix &m, const unsigned int nrows, const unsigned int ncols)
{
	m.resize(nrows,ncols);
	for (unsigned r=0;r<nrows;r++)
		for (unsigned c=0;c<ncols;c++)
			m(r,c) = static_cast<float>( mrpt::random::randomGenerator.drawUniform(0.0, 3.0) );
}
