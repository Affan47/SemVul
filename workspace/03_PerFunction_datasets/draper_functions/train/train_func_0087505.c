get_dr32_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * cos(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return sin(m_angle_geod_rotX) * (-sin(m_angle_geod_rotY));
    }
return 0.0;
}
