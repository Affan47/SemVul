processPreview(const mrpt::obs::CObservation2DRangeScan &obs)
{
	using namespace mrpt::opengl;


	if( m_showPreview )
	{
		if( !m_win )
		{
			string caption = string("Preview of ")+m_sensorLabel;
			m_win = mrpt::gui::CDisplayWindow3D::Create( caption, 640, 480 );
			m_win->setCameraAzimuthDeg(180);
			m_win->setCameraElevationDeg(90);
			COpenGLScenePtr &theScene = m_win->get3DSceneAndLock();
			theScene->insert(CAxisPtr( CAxis::Create(-300,-300,-50, 300,300,50, 1.0, 3, true  ) ));
			m_win->unlockAccess3DScene();
		}

		if( m_win && m_win->isOpen() )
		{
			COpenGLScenePtr &theScene = m_win->get3DSceneAndLock();
			opengl::CPlanarLaserScanPtr laser;
			CRenderizablePtr obj = theScene->getByName("laser");
			if( !obj )
			{
				laser = opengl::CPlanarLaserScan::Create();
				laser->setName("laser");
				laser->setScan(obs);
				theScene->insert(laser);
			}
			else
			{
				laser = CPlanarLaserScanPtr(obj);
				laser->setScan(obs);
			}
			m_win->unlockAccess3DScene();
			m_win->forceRepaint();
		}
	}
}
