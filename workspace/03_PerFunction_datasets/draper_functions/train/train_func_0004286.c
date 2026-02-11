set_nodename(unsigned char *name)
{
    debuglog(("New node name is %s\n", name));


    LATServices::Instance()->remove_node(std::string((char*)get_local_node()));


    strcpy((char *)local_name, (char *)name);


    send_service_announcement(-1);

}
