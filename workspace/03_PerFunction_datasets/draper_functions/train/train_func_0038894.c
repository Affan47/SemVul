pwm_match(int level)
{
  unsigned int new_value = value.get();
  Dprintf(("%s::pwm_match() level=%d\n", name().c_str(), level));


  if(level == 1) {

      if (bridge_shutdown && (!eccpas || !(eccpas->get_value() & ECCPAS::ECCPASE)))
      {
          Dprintf(("bridge_shutdown=%d eccpas=%p ECCPAS=%x\n", bridge_shutdown, eccpas,
		eccpas ? eccpas->get_value() & ECCPAS::ECCPASE: 0));
	  for(int i = 0; i < 4; i++)
	  {
            if(m_PinModule[i])
	    {
		 m_PinModule[i]->setControl(0);
        	 m_PinModule[i]->updatePinModule();
	    }
	  }
	  bridge_shutdown = false;
      }

      ccprl->ccprh->pwm_value = ((value.get()>>4) & 3) | 4*ccprl->value.get();
      tmr2->pwm_dc(ccprl->ccprh->pwm_value, address);
      ccprl->ccprh->put_value(ccprl->value.get());
  }
  if( !pwm1con) {

    if (bridge_shutdown == false)
    {
        m_cOutputState = level ? '1' : '0';
        m_source[0]->setState(level ? '1' : '0');
        m_PinModule[0]->setSource(m_source[0]);
	source_active[0] = true;


        if(level && !ccprl->ccprh->pwm_value)
            m_source[0]->setState('0');

        m_PinModule[0]->updatePinModule();


    }
  }
  else
  {


      if (!bridge_shutdown)
      	drive_bridge(level, new_value);
  }
}
