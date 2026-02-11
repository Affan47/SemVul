send_LUT (Coolscan_t * s)
{
  wait_scanner (s);
  if (s->gamma_bind)
    {
      send_one_LUT (s, s->gamma, S_DQ_Reg1);
      if(s->LS>=2)
	{      send_one_LUT (s, s->gamma, S_DQ_Reg2);
	       send_one_LUT (s, s->gamma, S_DQ_Reg3);
               if(s->colormode&0x08)
	       { send_one_LUT (s, s->gamma, S_DQ_Reg9);
	       }

	}
    }
  else
    {
      send_one_LUT (s, s->gamma_r, S_DQ_Reg1);
      send_one_LUT (s, s->gamma_g, S_DQ_Reg2);
      send_one_LUT (s, s->gamma_b, S_DQ_Reg3);
      if(s->colormode&0x08)
      { send_one_LUT (s, s->gamma_r, S_DQ_Reg9);
      }
    }
  return 0;
}
