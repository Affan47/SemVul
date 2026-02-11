SMB_Connect_Server(SMB_Handle_Type Con_Handle,
				   char *server, char *NTdomain)

{ SMB_Handle_Type con;
  char temp[80], called[80], calling[100], *address, buf [20];
  int i;


  con = Con_Handle;

  if (Con_Handle == NULL) {

    if ((con = (struct SMB_Connect_Def *)malloc(sizeof(struct SMB_Connect_Def))) == NULL) {


      SMBlib_errno = SMBlibE_NoSpace;
      return NULL;
    }

  }


  strcpy(con -> service, "");
  strcpy(con -> username, "");
  strcpy(con -> password, "");
  strcpy(con -> sock_options, "");
  strcpy(con -> address, "");
  strcpy(con -> desthost, server);
  strcpy(con -> PDomain, NTdomain);
  strcpy(con -> OSName, SMBLIB_DEFAULT_OSNAME);
  strcpy(con -> LMType, SMBLIB_DEFAULT_LMTYPE);
  con -> first_tree = con -> last_tree = NULL;

  SMB_Get_My_Name(con -> myname, sizeof(con -> myname));

  con -> port = 0;


  con -> pid = getpid();
  con -> mid = con -> pid;
  con -> uid = 0;
  con -> gid = getgid();


  for (i=0; i < strlen(server); i++)
    called[i] = toupper(server[i]);

  called[strlen(server)] = 0;

  for (i=0; i < strlen(con -> myname); i++)
    calling[i] = toupper(con -> myname[i]);

  calling[strlen(con -> myname)] = 0;

  if (strcmp(con -> address, "") == 0)
    address = con -> desthost;
  else
    address = con -> address;

  con -> Trans_Connect = RFCNB_Call(called,
				    calling,
				    address,
				    con -> port);


  if (con -> Trans_Connect == NULL) {

    if (Con_Handle == NULL) {
      Con_Handle = NULL;
      free(con);
    }
    SMBlib_errno = -SMBlibE_CallFailed;
    return NULL;

  }

  return(con);

}
