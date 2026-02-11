globus_l_gass_server_ez_listen_callback(
				void * user_arg,
				globus_gass_transfer_listener_t listener)
{
    int rc;
    globus_gass_transfer_request_t request;


    rc=globus_gass_transfer_register_accept(&request,
				 (globus_gass_transfer_requestattr_t *)
				 user_arg,
				 listener,
				 globus_l_gass_server_ez_register_accept_callback,
				 (void *)listener);

    if(rc != GLOBUS_SUCCESS)
    {

	globus_gass_transfer_register_listen(
	    listener,
	    globus_l_gass_server_ez_listen_callback,
	    user_arg);
    }
}
