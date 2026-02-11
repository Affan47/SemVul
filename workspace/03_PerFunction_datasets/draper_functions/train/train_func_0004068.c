directBondAss(int& bnq, bool& test, bool& test1, const bool beq[NBONDSMAX][NBONDSMAX],
  const bool aeq[NATOMSMAX][NATOMSMAX], std::vector<int>& bqcounter, std::vector<int>& aqtested,
  std::vector<int>& bstested, std::vector<int>& bqtested, std::vector<int>& astested,
  const std::vector<int> ager, const neigbourlist bqconn, const neigbourlist bsconn, TSimpleMolecule * smol) {


  int bns,bs,as1,as2,aq2,aq1;
  bool whiletest;

  test=false;
  aq1=getBond(bnq)->at[0];
  as1=aqtested[aq1];
  if (as1<0) return;
  aq2=getBond(bnq)->at[1];
  bs=bqcounter[bnq];
  bns=0; as2=0;
  whiletest=true;
  if (bs<bsconn[as1].nb) while (whiletest) {
    bns=bsconn[as1].adjusted[bs];


    if (bstested[bns]<0) if (beq[bns][bnq]) {
      as2=smol->getBond(bns)->at[0];
      if (as2==as1) as2=smol->getBond(bns)->at[1];
      test=false;


      if ((ager[bnq]<0) && (astested[as2]>=0)) test=(aqtested[aq2]==as2);


      if ((ager[bnq]>=0) && (astested[as2]<0)) test=aeq[as2][aq2];
    };
    bs=bs+1;
    whiletest=(bs==bsconn[as1].nb) || test;
    whiletest=! whiletest;
  };

  if (test) {
    if (ager[bnq]>=0) {
      aqtested[aq2]=as2; astested[as2]=aq2;
    };
    bstested[bns]=bnq;
    bqtested[bnq]=bns;
  };
  bqcounter[bnq]=bs;
  test1=(bs==bsconn[as1].nb);
}
