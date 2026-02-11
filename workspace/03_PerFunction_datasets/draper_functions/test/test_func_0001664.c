rstart_bit()
{
    if (verbose)
        cout << "I2C::rstart_bit SCL=" << m_sspmod->get_SCL_State() <<
	    " SDI=" << m_sspmod->get_SDI_State() << endl;

    i2c_state = CLK_RSTART;
    phase = 0;
    m_sspmod->setSCL(false);

    if (!m_sspmod->get_SCL_State())
    {
	setBRG();
        m_sspmod->setSDA(true);
    }
    else
	bus_collide();


}
