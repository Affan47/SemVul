pf_capture_setup(netio_desc_t *nio,void **opt,
                            int argc,char *argv[])
{
   struct netio_filter_capture *c;
   int link_type;


   if (argc != 2)
      return(-1);


   pf_capture_free(nio,opt);


   if (!(c = malloc(sizeof(*c))))
      return(-1);

   if ((link_type = pcap_datalink_name_to_val(argv[0])) == -1) {
      fprintf(stderr,"NIO %s: unknown link type %s, assuming Ethernet.\n",
              nio->name,argv[0]);
      link_type = DLT_EN10MB;
   }


   if (!(c->desc = pcap_open_dead(link_type,8192))) {
      fprintf(stderr,"NIO %s: pcap_open_dead failure\n",nio->name);
      goto pcap_open_err;
   }


   if (!(c->dumper = pcap_dump_open(c->desc,argv[1]))) {
      fprintf(stderr,"NIO %s: pcap_dump_open failure (file %s)\n",
              nio->name,argv[0]);
      goto pcap_dump_err;
   }

   printf("NIO %s: capturing to file '%s'\n",nio->name,argv[1]);
   *opt = c;
   return(0);

 pcap_dump_err:
   pcap_close(c->desc);
 pcap_open_err:
   free(c);
   return(-1);
}
