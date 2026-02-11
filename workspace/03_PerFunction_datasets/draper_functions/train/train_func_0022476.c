transform_measurement_point(const enum coordinate_calculation_option& cco)
{

    Point BT = ((*this).m_cam_bore_calc.get_B());
    Rotation_matrix BR(     Rotation_matrix::math,
                            (*this).m_cam_bore_calc.get_B_rotx(),
                            (*this).m_cam_bore_calc.get_B_roty(),
                            (*this).m_cam_bore_calc.get_B_rotz(),
                            (*this).m_cam_bore_calc.get_B_drotx(),
                            (*this).m_cam_bore_calc.get_B_droty(),
                            (*this).m_cam_bore_calc.get_B_drotz());


    Point GT  = m_car_pos->get_position();
    Point GR_ = m_car_pos->get_rotation();
    Rotation_matrix GR(     Rotation_matrix::math,
                            GR_.get_X(),
                            GR_.get_Y(),
                            GR_.get_Z(),
                            GR_.get_dX(),
                            GR_.get_dY(),
                            GR_.get_dZ());

    if(cco == BPoint_bore::local)
    {

      m_car_measurement_point    = m_local_measurement_point.Rotation_with_std(BT,BR);
      m_global_measurement_point = m_car_measurement_point.Rotation_with_std(GT,GR);
    }

    if(cco == BPoint_bore::car)
    {

      m_local_measurement_point = m_car_measurement_point.RotationRueck_with_std(BT,BR);
      m_global_measurement_point = m_car_measurement_point.Rotation_with_std(GT,GR);
    }

    if(cco == BPoint_bore::global)
    {

     m_car_measurement_point = m_global_measurement_point.RotationRueck_with_std(GT,GR);
     m_local_measurement_point = m_car_measurement_point.RotationRueck_with_std(BT,BR);
    }

    m_local_measurement_point.set_PktNr(m_nr);
    m_car_measurement_point.set_PktNr(m_nr);
    m_global_measurement_point.set_PktNr(m_nr);
}
