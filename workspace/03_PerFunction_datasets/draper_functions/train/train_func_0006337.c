new_scl_edge(bool direction)
  {
    int curBusState = m_uState;
    if (verbose) {
      Vprintf(("I2CMaster::new_scl_edge: %d\n",direction));
      debug();
    }

    if ( direction ) {


      switch (m_uState) {
      case eI2CTransferD:
        if (readBit())
          setNextMicroState(eI2CTransferE, 5);
        else if (m_mState == eI2CTransfer)
          transferCompleted();
        else if (m_mState == eI2CStop)
          setNextMicroState(eI2CStopA, 5);
        break;

      case eI2CStopB:

        if (m_mState == eI2CStop) {
          setNextMacroState(eI2CIdleBus);
          stopCompleted();
        }
      default:
        ;
      }

    }  else  {


      Dprintf(("I2CMaster SCL : Falling edge,data=%d\n ",m_nextBit));
      debug();

      switch ( m_uState ) {

      case eI2CIdle :
        m_pSDA->setDrivingState(true);
        break;

      case eI2CStartC:
      case eI2CStartB:
        setNextMicroState(eI2CTransferC, 1000);

        m_pSCL->setDrivingState(false);


        startCompleted();
        break;

      case eI2CTransferA:


        if (m_bitCount)
          setNextMicroState(eI2CTransferB, 5);
        else
          transferCompleted();
        break;

      default :
        m_pSDA->setDrivingState(true);
        break;
      }
    }
    if ((bool)verbose && m_uState != curBusState) {
      Vprintf(("I2C_EE::new_scl_edge() new bus state = %d\n",m_uState));
      debug();
    }
  }
