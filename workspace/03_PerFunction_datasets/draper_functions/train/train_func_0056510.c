get_rotation_angle_std(ROT_MATRIX_TYPE type,double& drotX,double& drotY,double& drotZ) const
{

      if(type == Rotation_matrix::math)
      {
       drotX = m_angle_math_drotX;
       drotY = m_angle_math_drotY;
       drotZ = m_angle_math_drotZ;
      }


      if(type == Rotation_matrix::geodetic)
      {
       drotX = m_angle_geod_drotX;
       drotY = m_angle_geod_drotY;
       drotZ = m_angle_geod_drotZ;
      }


return isError;
}
