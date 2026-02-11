blli2text(char **pos,char **end,int *length,
  const struct atm_blli *blli)
{
    MAYBE("blli:");
    if (l2_proto2text(pos,end,length,blli)) return -1;
    return l3_proto2text(pos,end,length,blli);
}
