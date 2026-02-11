putProtoWho(ButRnet *net)  {
#if  HAVE_SYS_UTSNAME_H
  struct utsname  unameOut;
#endif
  struct passwd  *pw;
  char  *loginName;
  ButEnv  *env = net->env;
  ButNetMsg  protoOut;

  assert(MAGIC(net));
  protoOut.length = int_stdInt32(sizeof(protoOut.perType.protoWho));
  protoOut.type = int_stdInt32(BUTNET_PROTOWHO);
#if  HAVE_SYS_UTSNAME_H
  uname(&unameOut);
#endif
  if ((loginName = getlogin()) == NULL)  {
    pw = getpwuid(getuid());
    loginName = pw->pw_name;
  }
  strcpy(protoOut.perType.protoWho.proto, env->protocol);
  protoOut.perType.protoWho.proto[sizeof(protoOut.perType.protoWho.proto) -
				  1] = '\0';
  sprintf(protoOut.perType.protoWho.who, "%s@%s",
	  loginName,
#if  HAVE_SYS_UTSNAME_H
	  unameOut.nodename
#else
	  "unknown"
#endif
	  );
  butRnet_write(net, &protoOut);
}
