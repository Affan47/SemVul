advResolveRequest(q)

queue1_t *q ;

{

   int sd ;

   tsh_get_ot2 out ;


   if ((sd = get_socket()) == -1)

   {

        printf(" Cannot getsocket for tuple object. Call system operator. \n");

        exit (E_SOCKET);

   }

   if (!do_connect(sd, q->host, q->port))

    {

       close(sd) ;

       exit (E_CONNECT);

    }


   strcpy(out.name, q->expr) ;

   out.priority = htons(q->priority) ;

   out.length = htonl(q->reqLen) ;

   if (!writen(sd, (char *)&out, sizeof(tsh_get_ot2)))

    {

       close(sd) ;

       exit (E_CONNECT);

    }

   if (!writen(sd, q->data , q->reqLen))

    {

       close(sd) ;

       exit (E_CONNECT);

    }

   close(sd);


   return 0 ;

}
