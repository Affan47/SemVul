name(char *return_str,int len)
{

  if(!initialized)
    runtime_initialize();

  if (opcode & 0x80)
    snprintf(return_str,len,"%s\t[0x%x],[0x%x]",
	     gpsimObject::name().c_str(),
	     source, destination);
  else
    snprintf(return_str,len,"%s\t[0x%x],%s",
	     gpsimObject::name().c_str(),
	     source,
	     cpu_pic->registers[destination]->name().c_str());


  return(return_str);
}
