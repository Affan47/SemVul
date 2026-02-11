ibnlMakeSubsystemToSubsystemConn(
    char *fromPort, char *width, char *speed, char *toSystem, char *toPort) {
#ifdef DEBUG
    printf("  Connecting S-S port:%s to SubSys:%s/%s\n",
         fromPort, toSystem, toPort);
#endif
    IBSysInstPort *p_port =
      new IBSysInstPort(fromPort, toSystem, toPort, char2width(width),
                        char2speed(speed));
    gp_curInstDef->addPort(p_port);
  }
