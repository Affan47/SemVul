nmc93cX6_check_cs(struct nmc93cX6_group *g,u_int old,u_int new)
{
   int i,res;

   for(i=0;i<g->nr_eeprom;i++)
   {
      if (g->dout_status == EEPROM_DOUT_HIGH)
         g->state[i].dataout_val = 1;

      if (g->debug)
      {
         printf("EEPROM %s(%d): check_cs:  check_bit(old,new,select_bit) "
                "[%8.8x, %8.8x, %d (mask = %8.8x)] = %d\n",
                g->description, i,
                old, new, g->def[i]->select_bit, 1 << g->def[i]->select_bit,
                check_bit(old,new,g->def[i]->select_bit));
      }

      if ((res = check_bit(old,new,g->def[i]->select_bit)) != 0) {
         g->state[i].cmd_len = 0;
         g->state[i].cmd_val = 0;


         if (res == 2)
            g->state[i].state = EEPROM_STATE_WAIT_CMD;
         else
            g->state[i].state = EEPROM_STATE_INACTIVE;
      }
   }
}
