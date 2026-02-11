willoption (int option)
{
  int changeok = 0;
  void (*func) () = 0;


  DEBUG (debug_options, 1, printoption ("td: recv will", option));

  if (do_dont_resp[option])
    {
      do_dont_resp[option]--;
      if (do_dont_resp[option] && his_state_is_will (option))
	do_dont_resp[option]--;
    }
  if (do_dont_resp[option] == 0)
    {
      if (his_want_state_is_wont (option))
	{
	  switch (option)
	    {

	    case TELOPT_BINARY:
	      init_termbuf ();
	      tty_binaryin (1);
	      set_termbuf ();
	      changeok++;
	      break;

	    case TELOPT_ECHO:


	      not42 = 0;
	      break;

	    case TELOPT_TM:


	      if (lmodetype < KLUDGE_LINEMODE)
		{
		  lmodetype = KLUDGE_LINEMODE;
		  clientstat (TELOPT_LINEMODE, WILL, 0);
		  send_wont (TELOPT_SGA, 1);
		}
	      else if (lmodetype == NO_AUTOKLUDGE)
		lmodetype = KLUDGE_OK;


	      return;

	    case TELOPT_LFLOW:


	      slctab[SLC_XON].defset.flag &= ~SLC_LEVELBITS;
	      slctab[SLC_XON].defset.flag |= SLC_DEFAULT;
	      slctab[SLC_XOFF].defset.flag &= ~SLC_LEVELBITS;
	      slctab[SLC_XOFF].defset.flag |= SLC_DEFAULT;
	    case TELOPT_TTYPE:
	    case TELOPT_SGA:
	    case TELOPT_NAWS:
	    case TELOPT_TSPEED:
	    case TELOPT_XDISPLOC:
	    case TELOPT_NEW_ENVIRON:
	    case TELOPT_OLD_ENVIRON:
	      changeok++;
	      break;

	    case TELOPT_LINEMODE:


	      lmodetype = REAL_LINEMODE;
	      func = doclientstat;
	      changeok++;
	      break;

#ifdef	AUTHENTICATION
	    case TELOPT_AUTHENTICATION:
	      func = auth_request;
	      changeok++;
	      break;
#endif

#ifdef	ENCRYPTION
	    case TELOPT_ENCRYPT:
	      func = encrypt_send_support;
	      changeok++;
	      break;
#endif

	    default:
	      break;
	    }
	  if (changeok)
	    {
	      set_his_want_state_will (option);
	      send_do (option, 0);
	    }
	  else
	    {
	      do_dont_resp[option]++;
	      send_dont (option, 0);
	    }
	}
      else
	{


	  switch (option)
	    {
	    case TELOPT_ECHO:
	      not42 = 0;


	      send_dont (option, 1);


	      break;
	    case TELOPT_LINEMODE:


	      lmodetype = REAL_LINEMODE;
	      func = doclientstat;
	      break;

#ifdef	AUTHENTICATION
	    case TELOPT_AUTHENTICATION:
	      func = auth_request;
	      break;
#endif

#ifdef	ENCRYPTION
	    case TELOPT_ENCRYPT:
	      func = encrypt_send_support;
	      break;
#endif
	    case TELOPT_LFLOW:
	      func = flowstat;
	      break;
	    }
	}
    }
  set_his_state_will (option);
  if (func)
    (*func) ();
}
