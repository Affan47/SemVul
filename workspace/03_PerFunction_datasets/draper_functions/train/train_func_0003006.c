dev_i8255x_process_ru_cmd(struct i8255x_data *d,u_int ruc)
{
   switch(ruc) {

      case RU_CMD_NOP:
         break;


      case RU_CMD_START:
         d->ru_offset = d->scb_gptr;
         d->ru_state  = RU_STATE_READY;
         break;


      case RU_CMD_RESUME:
         dev_i8255x_ru_resume(d);
         break;


      case RU_CMD_LOAD_RU_BASE:
         d->ru_base = d->scb_gptr;
         break;

      default:
         EEPRO_LOG(d,"unsupported RU command 0x%2.2x\n",ruc);
   }
}
