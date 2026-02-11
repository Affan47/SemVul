cmd_create(hypervisor_conn_t *conn,int argc,char *argv[])
{
   atm_bridge_t *t;

   if (!(t = atm_bridge_create(argv[0]))) {
      hypervisor_send_reply(conn,HSC_ERR_CREATE,1,
                            "unable to create ATM bridge '%s'",
                            argv[0]);
      return(-1);
   }

   atm_bridge_release(argv[0]);
   hypervisor_send_reply(conn,HSC_INFO_OK,1,"ATM bridge '%s' created",argv[0]);
   return(0);
}
