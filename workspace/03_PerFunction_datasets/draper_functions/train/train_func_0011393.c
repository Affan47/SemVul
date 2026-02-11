strrv2d_(int *ConTxt, F_CHAR uplo, F_CHAR diag, int *m, int *n,
                     float *A, int *lda, int *rsrc, int *csrc)
#endif


{


   void BI_ArgCheck(int, int, char *, char, char, char, int, int, int, int,
                    int *, int *);
   BI_MPI_Datatype BI_GetMpiTrType(BLACSCONTEXT *, char, char, int, int, int,
                                   BI_MPI_Datatype, int *);
   void BI_Unpack(BLACSCONTEXT *, BVOID *, BLACBUFF *, BI_MPI_Datatype);
   void BI_Srecv(BLACSCONTEXT *, int, int, BLACBUFF *);
   void BI_UpdateBuffs(BLACBUFF *);
   BLACBUFF *BI_GetBuff(int);
   int BI_BuffIsFree(BLACBUFF *, int);
   int tuplo, tdiag, tlda;
   int ierr, length;
   BLACBUFF *bp;
   BI_MPI_Datatype MatTyp;
   BLACSCONTEXT *ctxt;
   extern BLACBUFF BI_AuxBuff, *BI_ActiveQ;

   MGetConTxt(Mpval(ConTxt), ctxt);
   tdiag = F2C_CharTrans(diag);
   tuplo = F2C_CharTrans(uplo);
   tdiag = Mlowcase(tdiag);
   tuplo = Mlowcase(tuplo);

#if (BlacsDebugLvl > 0)
   BI_ArgCheck(Mpval(ConTxt), RT_RV, __FILE__, 'a', tuplo, tdiag, Mpval(m),
               Mpval(n), Mpval(lda), 1, Mpaddress(rsrc), Mpaddress(csrc));
#endif
   if (Mpval(lda) < Mpval(m)) tlda = Mpval(m);
   else tlda = Mpval(lda);
   ctxt->scp = &ctxt->pscp;

   MatTyp = BI_GetMpiTrType(ctxt, tuplo, tdiag, Mpval(m), Mpval(n), tlda,
                            BI_MPI_FLOAT, &BI_AuxBuff.N);
   BI_AuxBuff.Buff = (char *) A;
   BI_AuxBuff.dtype = MatTyp;
   BI_Srecv(ctxt, Mkpnum(ctxt, Mpval(rsrc), Mpval(csrc)), PT2PTID, &BI_AuxBuff);
   BI_MPI_Type_free(&MatTyp, ierr);
   if (BI_ActiveQ) BI_UpdateBuffs(NULL);
}
