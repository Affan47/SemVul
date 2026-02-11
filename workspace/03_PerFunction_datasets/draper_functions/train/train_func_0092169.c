mtog() {
    int indi;

    char    temp[LONGTEXT];


    Cpystr(temp, data.macke.seqabbr);

    for(indi=Lenstr(temp); indi<13; temp[indi++] = ' ') ;

    if(Lenstr(data.macke.date)>1)

        sprintf((temp+10),
                "%7d bp    RNA             RNA       %s\n",
                data.seq_length, genbank_date(data.macke.date));

    else sprintf((temp+10),
                 "%7d bp    RNA             RNA       %s\n",
                 data.seq_length, genbank_date(today_date()));

    replace_entry(&(data.gbk.locus), temp);


    if(Lenstr(data.macke.name)>1)   {
        replace_entry(&(data.gbk.organism), data.macke.name);


        Append_char(&(data.gbk.organism), '.');
    }

    if(Lenstr(data.macke.rna)>1)    {
        data.gbk.comments.seqinf.exist = 1;
        replace_entry(&(data.gbk.comments.seqinf.methods),
                      data.macke.rna);
    }
    if(Lenstr(data.macke.acs)>1)    {


        data.gbk.comments.seqinf.exist = 1;
        replace_entry(&(data.gbk.comments.seqinf.gbkentry),
                      data.macke.acs);
    }   else if(Lenstr(data.macke.nbk)>1)   {


        data.gbk.comments.seqinf.exist = 1;
        replace_entry(&(data.gbk.comments.seqinf.gbkentry),
                      data.macke.nbk);
    }
    if(Lenstr(data.macke.atcc)>1)   {
        data.gbk.comments.orginf.exist = 1;
        replace_entry(&(data.gbk.comments.orginf.cc),
                      data.macke.atcc);
    }
    mtog_decode_ref_and_remarks();

    if(Lenstr(data.gbk.comments.orginf.cc)<=1&&Lenstr(data.macke.atcc)>1){
        replace_entry(&(data.gbk.comments.orginf.cc),
                      data.macke.atcc);
    }


    mtog_genbank_def_and_source();

    return(1);
}
