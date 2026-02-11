readAvailable(int handle) {
  NetConnection *net;
  char line[2048];
  int gotinput, loopc;

  global.debug("MainWindow","readAvailable");
  net = global.network;

  if ((net==NULL)||(!net->isConnected())||(global.protocol==NULL)) {
    cleanUpConnection();
    return;
  }

  if (handle == net->getReadHandle()) {

    loopc = 0;
    do {
      gotinput=0;
      if (net->readLine(line,2048)==0) {
	gotinput=1;
	global.protocol->receiveString(line);
	global.agentBroadcast(line);
      } else {
	if (global.protocol->hasAuthenticationPrompts())
	  if ((net->bufferMatch("login:"))||
	      (net->bufferMatch("password:")))
	    if (net->readPartial(line,2048)==0) {
	      global.protocol->receiveString(line);
	      global.agentBroadcast(line);
	      gotinput=1;
	    }
      }
      ++loopc;
      if (loopc%10 == 9)
	gtk_main_iteration();

      if ( (global.network==0) || (global.protocol==0) )
	break;

    } while(gotinput);

  } else {

    if (io_tag < 0)
      io_tag = gtk_timeout_add(200, mainwindow_read_agents, (gpointer) this);
  }

}
