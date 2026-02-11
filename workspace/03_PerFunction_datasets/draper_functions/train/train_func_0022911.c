slave_command()
{
    unsigned int sspcon_val = m_sspcon->value.get();
    unsigned int sspstat_val = m_sspstat->value.get();

    if (verbose)
	cout << "I2C::slave_command m_SSPsr=" << hex << m_SSPsr << endl;
    if ( m_SSPsr == 0 && (m_sspcon2->value.get() & _SSPCON2::GCEN))
    {
	i2c_state = RX_DATA;
    }
    else
    {
	if (verbose)
	    cout << "I2c::slave_command i2c_state=" << i2c_state << " sspcon=" << sspcon_val << endl;
    	switch( sspcon_val & _SSPCON::SSPM_mask )
	{
      	case _SSPCON::SSPM_I2Cslave_10bitaddr_ints:
      	case _SSPCON::SSPM_I2Cslave_10bitaddr:
		if (i2c_state == RX_CMD && (m_SSPsr & 1))
		{
		    sspstat_val |= _SSPSTAT::RW;
		    i2c_state = TX_DATA;
	    	    m_sspmod->setSCL(false);
	    	    sspcon_val &= ~ _SSPCON::CKP;
	    	    m_sspcon->put_value(sspcon_val);
		}
		else
		{
	       	    sspstat_val |= _SSPSTAT::UA;
		    i2c_state = (i2c_state == RX_CMD2) ?
			RX_DATA : RX_CMD2;
		}
		break;

      	case _SSPCON::SSPM_I2Cslave_7bitaddr:
      	case _SSPCON::SSPM_I2Cslave_7bitaddr_ints:
		if (i2c_state == RX_CMD && (m_SSPsr & 1))
		{
		    sspstat_val |= _SSPSTAT::RW;
	            sspstat_val &= ~_SSPSTAT::BF;
	    	    i2c_state = TX_DATA;
		    sspcon_val &= ~ _SSPCON::CKP;
		    m_sspcon->put_value(sspcon_val);
		    m_sspmod->setSCL(false);
		}
		else
		{
		    i2c_state = RX_DATA;
		}
		break;
	}
    	m_sspstat->put_value(sspstat_val);
    }
}
