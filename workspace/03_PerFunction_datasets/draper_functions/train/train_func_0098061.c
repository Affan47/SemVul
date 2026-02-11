cmd_send_con_msg(hypervisor_conn_t *conn,int argc,char *argv[])
{
   vm_instance_t *vm;

   if (!(vm = hypervisor_find_object(conn,argv[0],OBJ_TYPE_VM)))
      return(-1);

   vtty_store_str(vm->vtty_con,argv[1]);

   vm_release(vm);
   hypervisor_send_reply(conn,HSC_INFO_OK,1,"OK");
   return(0);
}
