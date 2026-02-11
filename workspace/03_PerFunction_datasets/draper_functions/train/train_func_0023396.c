e_putchar(plain)
unsigned char plain;
{
  fprintf(ofp,"%02X",encrypt_char(plain));
  ecol+=2;
  if(ecol==64){putc('\n',ofp);ecol=0;}
}
