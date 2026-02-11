addBPoint(double m, double n)
{
  if( lCam_bore.size() && ( m_saved_cams == (m_used_cams+1) ) )
    {

      Cam_bore cam_bore(*lCam_bore.rbegin());
      Cam *cam=new Cam(cam_bore);

      BPoint bp(*cam,m,n);


      I.m_m = m;
      I.m_n = n;


      lBPoint.push_back( bp );


      m_is_set_mn = true;
      m_used_cams+=1;

      return true;
    }
  else
    {

      cerr << "ERROR -> create BPoint not possible!";
      return false;
    }
}
