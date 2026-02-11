get_rotation_angle_math(double& rotX,double& rotY,double& rotZ)
{
    if(m_R.getCol()==3 && m_R.getRow()==3)
    {

          double r11 =m_R(0,0);
          double r12 =m_R(0,1);
          double r13 =m_R(0,2);
          double r21 =m_R(1,0);
          double r22 =m_R(1,1);
          double r23 =m_R(1,2);
          double r31 =m_R(2,0);
          double r32 =m_R(2,1);
          double r33 =m_R(2,2);

          double threshold = 9.99999e-13;
          if(fabs(r11)<threshold) r11=0.0;
          if(fabs(r21)<threshold) r21=0.0;
          if(fabs(r31)<threshold) r31=0.0;
          if(fabs(r12)<threshold) r12=0.0;
          if(fabs(r22)<threshold) r22=0.0;
          if(fabs(r32)<threshold) r32=0.0;
          if(fabs(r13)<threshold) r13=0.0;
          if(fabs(r23)<threshold) r23=0.0;
          if(fabs(r33)<threshold) r33=0.0;

          rotY = asin(r13);

          if(r23||r33)
           rotX = atan2(-r23,r33);
          else
           rotX = atan2(-r22,r32);


          if(r12||r11)
           rotZ = atan2(-r12,r11);
          else
           rotZ = atan2(-r22,r21);


          if(fabs(r13-1.0) < threshold || fabs(r13+1.0) < threshold)
          {
            if(r32||r22)
            {
             rotX = atan2(r32,r22);
             rotZ = 0.0;
            }
            else
            {
             rotX = 0.0;
             rotZ = atan2(r21,r22);
            }
          }

          rotX = clamp(rotX, -PI, PI);
          rotY   = clamp(rotY  , -PI, PI);
          rotZ = clamp(rotZ, -PI, PI);

    }
    else
    {
     isError=true;
     m_errorstring="No matrix available!!";
     return false;
    }
return true;
}
