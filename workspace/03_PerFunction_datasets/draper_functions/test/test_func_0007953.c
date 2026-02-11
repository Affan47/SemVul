sort_cmd(void)
{
  int i;
  word curr_vb;
  word all_word, global_word;

  verbptr=rmalloc(sizeof(short)*TOTAL_VERB);
  verbend=rmalloc(sizeof(short)*TOTAL_VERB);

  if (mars_fix) {
    for(i=0;i<TOTAL_VERB;i++) {
      verbptr[i]=0;
      verbend[i]=last_cmd;}
    return;
  }

#ifdef SORT_META
  if (!agx_file && aver>=AGX00) rsort();
#endif


  if (no_auxsyn) return;

  for(i=0;i<TOTAL_VERB;i++) {
    verbptr[i]=last_cmd;
    verbend[i]=0;
  }

  all_word=search_dict("all");
  if (all_word==0) all_word=-1;

  global_word=search_dict("global_scope");
  if (global_word==0) global_word=-1;


  for(i=0;i<last_cmd;i++) {
    if (command[i].actor<0) continue;
    if (command[i].nouncmd==all_word)

      verbflag[cmdverb_code(command[i].verbcmd)]|=VERB_MULTI;
    if (command[i].actor>1)
      curr_vb=DIR_ADDR_CODE;
    else
      curr_vb=cmdverb_code(command[i].verbcmd);
    if (i<verbptr[curr_vb]) verbptr[curr_vb]=i;
    if (i>verbend[curr_vb]) verbend[curr_vb]=i;
  }

  for(i=0;i<TOTAL_VERB;i++)
    if (verbptr[i]==last_cmd)
      verbend[i]=last_cmd;
    else verbend[i]++;

  for(i=0;i<TOTAL_VERB;i++) {
    int j;

    j=synlist[i];
    if (syntbl[j]==0) continue;
    while(syntbl[j]!=0) j++;
    j--;
    if (syntbl[j]==global_word) {
      verbflag[i]|=VERB_GLOBAL;
      syntbl[j]=0;
    }
  }
}
