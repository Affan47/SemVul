httpKillConnection ( connection )
sockfd connection;
{
  int loop, newnum;


  for ( loop = 0, newnum = 0; loop < num_requests; loop++ ) {
    if ( requests[loop]->connection == connection ) {

      if ( requests[loop]->data_read )
        free ( requests[loop]->data_read );
      if ( requests[loop]->request )
        free ( requests[loop]->request );
      free ( requests[loop] );
      requests[loop] = NULL;
    }
    else {
      requests[newnum] = requests[loop];
    }
  }

  for ( loop = 0, newnum = 0; loop < num_requests; loop++ ) {
    if ( requests[loop] && loop != newnum ) {
      requests[newnum] = requests[loop];
      requests[loop] = NULL;
      newnum++;
    }
  }

  num_requests = newnum;

  closesocket ( connection );
  return ( HTTP_NO_ERROR );
}
