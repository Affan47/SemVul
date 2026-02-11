envia_icmp_err ( char *buffer, struct my_pack *packet )
{
  struct icmp2 *icp = (struct icmp2 *) buffer;
  union data_hdr *mix = (union data_hdr *) malloc(TCAB_64DATA);
  int elemento, tam;

  if ( !mix )
      salir(12);

  iniciamem( mix, TCAB_64DATA);

  icp->icmp_type   = packet->tipo_icmp;
  icp->icmp_code   = packet->cod_icmp;
  icp->icmp_cksum  = 0;

  icp->icmp_gwaddr.s_addr = 0;

  icp->icmp_ip.ip_hl  = TCAB_IP >> 2;
  icp->icmp_ip.ip_v   = 4;
  icp->icmp_ip.ip_tos = 0x0000;
  icp->icmp_ip.ip_len = htons( TCAB_IP + TCAB_ICMP + TCAB_64DATA);
  icp->icmp_ip.ip_id  = htons(0x4A2F);
  icp->icmp_ip.ip_off = 0x0000;
  icp->icmp_ip.ip_ttl = TTL_DFL;
  icp->icmp_ip.ip_p   = packet->protocol;
  icp->icmp_ip.ip_sum = 0x0000;

  switch( packet->tipo_icmp )
  {
     case ICMP_REDIRECT: icp->icmp_ip.ip_src.s_addr = packet->orig;
                         icp->icmp_ip.ip_dst.s_addr = packet->dest_red;
                         icp->icmp_gwaddr.s_addr = packet->gway;
                         break;
     case ICMP_PARAM_PROB: icp->icmp_pptr = packet->pointer;
                  default: icp->icmp_ip.ip_src.s_addr = packet->destino.sin_addr.s_addr;
                           icp->icmp_ip.ip_dst.s_addr = packet->orig;
  }

  icp->icmp_ip.ip_sum = in_cksum( (u_short *)(&(icp->icmp_ip)), TCAB_IP );

  for ( elemento=0; elemento < MAX(data_protocols); elemento++ )
  {
     if ( packet->protocol == data_protocols[elemento].proto )
     {
        (*data_protocols[elemento].func_proto)( mix, packet->p_origen,
         packet->p_destino);
        elemento=32767;
        break;
     }
  }

  if ( elemento != 32767)
     salir(10);

  copymem( mix, icp + 1, TCAB_64DATA );

  tam = add_garbage( buffer, packet->garbage, (TCAB_ICMP + TCAB_64DATA) );

  icp->icmp_cksum = in_cksum( (u_short *)icp, tam );

  return( tam );
}
