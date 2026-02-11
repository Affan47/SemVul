debugDumpInFiles( const std::string &ptg_name ) const
{
	using namespace mrpt::system;
	using namespace std;

	const char *sPath = CParameterizedTrajectoryGenerator::OUTPUT_DEBUG_PATH_PREFIX.c_str();

	mrpt::system::createDirectory( sPath );
	mrpt::system::createDirectory( mrpt::format("%s/PTGs",sPath) );

	const string sFilTxt_x   = mrpt::format("%s/PTGs/PTG%s_x.txt",sPath,ptg_name.c_str() );
	const string sFilTxt_y   = mrpt::format("%s/PTGs/PTG%s_y.txt",sPath,ptg_name.c_str() );
	const string sFilTxt_phi = mrpt::format("%s/PTGs/PTG%s_phi.txt",sPath,ptg_name.c_str() );
	const string sFilTxt_t   = mrpt::format("%s/PTGs/PTG%s_t.txt",sPath,ptg_name.c_str() );
	const string sFilTxt_d   = mrpt::format("%s/PTGs/PTG%s_d.txt",sPath,ptg_name.c_str() );

	ofstream fx(sFilTxt_x.c_str());  if (!fx.is_open()) return false;
	ofstream fy(sFilTxt_y.c_str());  if (!fy.is_open()) return false;
	ofstream fp(sFilTxt_phi.c_str());if (!fp.is_open()) return false;
	ofstream fd(sFilTxt_d.c_str());  if (!fd.is_open()) return false;

	const size_t nPaths = getAlphaValuesCount();


	fx << "% PTG data file for 'x'. Each row is the trajectory for a different 'alpha' parameter value." << endl;
	fy << "% PTG data file for 'y'. Each row is the trajectory for a different 'alpha' parameter value." << endl;
	fp << "% PTG data file for 'phi'. Each row is the trajectory for a different 'alpha' parameter value." << endl;
	fd << "% PTG data file for 'd'. Each row is the trajectory for a different 'alpha' parameter value." << endl;

	vector<size_t> path_length(nPaths);
	for (size_t k=0;k<nPaths;k++)
		path_length[k] = getPathStepCount(k);

	size_t maxPoints=0;
	for (size_t k=0;k<nPaths;k++)
		maxPoints = max( maxPoints, path_length[k] );

	for (size_t k=0;k<nPaths;k++)
	{
		for (size_t n=0;n< maxPoints;n++)
		{
			const size_t nn = std::min( n, path_length[k]-1 );
			mrpt::math::TPose2D p;
			this->getPathPose(k,nn, p);
			fx << p.x << " ";
			fy << p.y << " ";
			fp << p.phi << " ";
			fd << this->getPathDist(k,nn) << " ";
		}
		fx << endl;
		fy << endl;
		fp << endl;
		fd << endl;
	}

	return true;
}
