setAngle( double angle, const uint8_t servo, bool fast )
{


	if( angle < -m_TruncateFactor*M_PI/2 )	angle = -m_TruncateFactor*M_PI/2;
	if( angle > m_TruncateFactor*M_PI/2 )	angle = m_TruncateFactor*M_PI/2;

	unsigned int reg = angle2RegValue( m_offsets[servo]+angle );

	std::cout << "Angle: " << RAD2DEG( angle ) << " - Reg: " << reg << std::endl;
	return setRegisterValue( reg, servo, fast );

}
