get_dr13_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) + cos(m_angle_geod_rotX) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}
