match_addresses(Elan_t *elan, unsigned char *addr)
{
  int i,j,match=0;
  unsigned char tmp;

  for(i=0;i<elan->no_addresses && !match;i++) {
    match=1;
    for(j=0;j<ATM_ESA_LEN && match;j++) {
      if (elan->addresses[i][j*2] == 'x' ||
	  elan->addresses[i][j*2] == 'X') {
	tmp = addr[j]&0xf0;
      } else {
	if (elan->addresses[i][j*2] >= '0' &&
	    elan->addresses[i][j*2] <= '9') {
	  tmp = (elan->addresses[i][j*2]-'0')<<4;
	} else {
	  tmp = (tolower(elan->addresses[i][j*2])-'a'+10)<<4;
	}
      }
      if (elan->addresses[i][j*2+1] == 'x' ||
	  elan->addresses[i][j*2+1] == 'X') {
	tmp |= addr[j]&0xf;
      } else {
	if (elan->addresses[i][j*2+1] >= '0' &&
	    elan->addresses[i][j*2+1] <= '9') {
	  tmp |= 0xf&(elan->addresses[i][j*2+1]-'0');
	} else {
	  tmp |= 0xf&(tolower(elan->addresses[i][j*2+1])-'a'+10);
	}
      }

      if (addr[j] != tmp)
	match=0;
    }
  }
  return match;
}
