AB(const double x_coord1, const double y_coord1, const double x_coord2, const double y_coord2, const double x_val1, const double y_val1, const double x_val2, const double y_val2){

	if (0.0 == (x_val2 - x_val1)){
		m_Ax_ValToCoord = 0.0;
		m_Bx_ValToCoord = 0.0;
	}else{
		m_Ax_ValToCoord = (x_coord2 - x_coord1) / (x_val2 - x_val1);
		m_Bx_ValToCoord = x_coord1 - (m_Ax_ValToCoord * x_val1);
	}
	if (0.0 == (y_val2 - y_val1)){
		m_Ay_ValToCoord = 0.0;
		m_By_ValToCoord = 0.0;
	}else{
		m_Ay_ValToCoord = (y_coord2 - y_coord1) / (y_val2 - y_val1);
		m_By_ValToCoord = y_coord1 - (m_Ay_ValToCoord * y_val1);
	}

	if (0.0 == (x_coord2 - x_coord1)){
		m_Ax_CoordToVal = 0.0;
		m_Bx_CoordToVal = 0.0;
	}else{
		m_Ax_CoordToVal = (x_val2 - x_val1) / (x_coord2 - x_coord1);
		m_Bx_CoordToVal = x_val1 - (m_Ax_CoordToVal * x_coord1);
	}
	if (0.0 == (y_coord2 - y_coord1)){
		m_Ay_CoordToVal = 0.0;
		m_By_CoordToVal = 0.0;
	}else{
		m_Ay_CoordToVal = (y_val2 - y_val1) / (y_coord2 - y_coord1);
		m_By_CoordToVal = y_val1 - (m_Ay_CoordToVal * y_coord1);
	}
}
