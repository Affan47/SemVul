set(gint64 v)
  {
    gint64 i64;
    get(i64);
    int diff = (i64 ^ v) &0xfff;
    Integer::set(v);

    if (m_pCpu)
    {
      P18F2x21 *pCpu21 = (P18F2x21*)m_pCpu;

      if (diff & MCLRE)
        (v & MCLRE) ? m_pCpu->assignMCLRPin(1) : m_pCpu->unassignMCLRPin();
      if ( pCpu21->adcon1 )
      {
        unsigned int pcfg = (v & PBADEN) ? 0
                           : (ADCON1::PCFG0 | ADCON1::PCFG1 | ADCON1::PCFG2);
        pCpu21->adcon1->por_value=RegisterValue(pcfg,0);
      }
      if ( diff & CCP2MX )
      {
        if ( v & CCP2MX )
          pCpu21->ccp2con.setIOpin(&((*pCpu21->m_portc)[1]));
        else
          pCpu21->ccp2con.setIOpin(&((*pCpu21->m_portb)[3]));
      }
    }
  }
