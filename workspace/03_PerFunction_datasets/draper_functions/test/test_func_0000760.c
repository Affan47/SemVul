cmd_create_vpc(hypervisor_conn_t *conn,int argc,char *argv[])
{
   atmsw_table_t *t;

   if (!(t = hypervisor_find_object(conn,argv[0],OBJ_TYPE_ATMSW)))
      return(-1);


   if (atmsw_create_vpc(t,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) == -1) {
      atmsw_release(argv[0]);
      hypervisor_send_reply(conn,HSC_ERR_BINDING,1,"unable to create VPC");
      return(-1);
   }

   atmsw_release(argv[0]);
   hypervisor_send_reply(conn,HSC_INFO_OK,1,"VPC created");
   return(0);
}
