ckpSPI(unsigned int value)
{
    if(m_spi && !m_spi->isIdle())
      cout << "SPI: You just changed CKP in the middle of a transfer." << endl;

    switch( value & _SSPCON::SSPM_mask ) {
    case _SSPCON::SSPM_SPImaster4:
    case _SSPCON::SSPM_SPImaster16:
    case _SSPCON::SSPM_SPImaster64:
    case _SSPCON::SSPM_SPImasterAdd:
      if (m_SckSource) m_SckSource->putState( (value & _SSPCON::CKP) ? '1' : '0' );
      break;
    case _SSPCON::SSPM_SPImasterTMR2:
      break;
    }
}
