initialize(){

	init(m_ptu_port,laser.getSerialPort());


	m_initial = DEG2RAD(m_initial);
	m_final = DEG2RAD(m_final);


	if ( ((!m_ptu_type) && (m_initial < m_final)) || ((m_ptu_type==1) && (m_initial > m_final)) ) {

		double aux;
		aux = m_initial;
		m_initial = m_final;
		m_final = aux;

	}

	if (!m_ptu_type) {

		const double defSpeed = 0.897598;


		ptu->speed(m_axis,defSpeed);
		ptu->aWait();


		ptu->moveToAbsPos(m_axis,m_initial);
		ptu->aWait();
		mrpt::system::sleep(2000);


		int initialPos = ptu->radToPos(m_axis,m_initial);
		m_initial = ptu->posToRad(m_axis,(long) initialPos);
		int finalPos = ptu->radToPos(m_axis,m_final);
		m_final = ptu->posToRad(m_axis, (long) finalPos);


		ptu->speed(m_axis,m_velocity);
		ptu->aWait();


		ptu->moveToAbsPos(m_axis,m_final);


	} else if (m_ptu_type == 1) {

		const double defSpeed = 26;
		ptu->speed(0,DEG2RAD(defSpeed));

		ptu->reset();

		double status;
		ptu->status(status);


		while(status) {
			mrpt::system::sleep(2);
			ptu->status(status);
		}


		ptu->moveToAbsPos(m_axis,m_initial);

		ptu->status(status);
		while(status) {
			mrpt::system::sleep(2);
			ptu->status(status);
		}


		ptu->speed(m_axis,DEG2RAD(m_velocity));
		ptu->moveToAbsPos(m_axis,m_final);

	}

}
