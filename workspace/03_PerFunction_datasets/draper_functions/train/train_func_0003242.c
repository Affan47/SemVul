chksol()


{
 ps_t ps;
 grabchps(&ps);
 if (ps.ps_column != 2)
   {
    ps.ps_column--;
    sprintf(linet1,"@%c is legal only at the start of a line.",ch);
    lr_err(&ps,linet1);
   }
}
