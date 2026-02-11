putgenericT(befig_list* befig, char* name, double Thl_value, double Tll_value, double Tlh_value, double Thh_value)
{
   char* Thl, *Tll, *Tlh, *Thh;
   char memo;
   char *output;

   if (befig->BEOUT) output=befig->BEOUT->NAME;
   else if (befig->BEBUS) output=befig->BEBUS->NAME;
   else {
      fprintf(stderr,"BEH: output is missing in %s\n",befig->NAME);
      autexit(1);
   }

   memo=SEPAR;
   SEPAR='_';
   Thl=concatname(Tphl,name);
   Tll=concatname(Tpll,name);
   Thh=concatname(Tphh,name);
   Tlh=concatname(Tplh,name);
   Thl=concatname(Thl,output);
   Tll=concatname(Tll,output);
   Thh=concatname(Thh,output);
   Tlh=concatname(Tlh,output);
   SEPAR=memo;

   befig->BEGEN=beh_addbegen(befig->BEGEN,Thl,namealloc("natural"),
               putvalue((int)Thl_value));
   befig->BEGEN=beh_addbegen(befig->BEGEN,Tll,namealloc("natural"),
               putvalue((int)Tll_value));
   befig->BEGEN=beh_addbegen(befig->BEGEN,Tlh,namealloc("natural"),
               putvalue((int)Tlh_value));
   befig->BEGEN=beh_addbegen(befig->BEGEN,Thh,namealloc("natural"),
               putvalue((int)Thh_value));
}
