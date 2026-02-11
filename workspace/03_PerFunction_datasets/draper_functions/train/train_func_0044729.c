stun_addr_encode(const ioa_addr* ca, u08bits *cfield, int *clen, int xor_ed, u32bits mc, const u08bits *tsx_id) {

  if(!cfield || !clen || !ca || !tsx_id) return -1;

  if (ca->ss.sa_family == AF_INET || ca->ss.sa_family==0) {


    *clen=8;

    cfield[0]=0;
    cfield[1]=1;

    if (xor_ed) {


      ((u16bits*)cfield)[1] = (ca->s4.sin_port) ^ nswap16(mc >> 16);


      ((u32bits*)cfield)[1] = (ca->s4.sin_addr.s_addr) ^ nswap32(mc);

    } else {


      ((u16bits*)cfield)[1]=ca->s4.sin_port;


      ((u32bits*)cfield)[1]=ca->s4.sin_addr.s_addr;
    }

  } else if (ca->ss.sa_family == AF_INET6) {


    *clen=20;

    cfield[0]=0;
    cfield[1]=2;

    if (xor_ed) {

      unsigned int i;
      u08bits *dst = ((u08bits*)cfield)+4;
      const u08bits *src = (const u08bits*)&(ca->s6.sin6_addr);
      u32bits magic = nswap32(mc);


      ((u16bits*)cfield)[1] = ca->s6.sin6_port ^ nswap16(mc >> 16);


      for (i=0; i<4; ++i) {
	dst[i] = (u08bits)(src[i] ^ ((const u08bits*)&magic)[i]);
      }
      for (i=0; i<12; ++i) {
	dst[i+4] = (u08bits)(src[i+4] ^ tsx_id[i]);
      }

    } else {


      ((u16bits*)cfield)[1]=ca->s6.sin6_port;


      ns_bcopy(&ca->s6.sin6_addr, ((u08bits*)cfield)+4, 16);
    }

  } else {
    return -1;
  }

  return 0;
}
