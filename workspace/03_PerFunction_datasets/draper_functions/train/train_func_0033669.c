opr_tbl_opstr(unsigned commid)


#ifdef DOC
unsigned        commid     ;
#endif


{
   int opnum = 0;
   while ( opnum < NumOperators ) {
      if (opr_tbl_commid(opnum)==commid)
	return opnum;
      opnum++;
   }
   return -1;
}
