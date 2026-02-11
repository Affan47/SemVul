_TwoFish_BlockCrypt(u_int8_t *in,u_int8_t *out,u_int32_t size,int decrypt,TWOFISH *tfdata)
{	u_int8_t PnMinusOne[TwoFish_BLOCK_SIZE];
  u_int8_t CnMinusOne[TwoFish_BLOCK_SIZE];
  u_int8_t CBCplusCprime[TwoFish_BLOCK_SIZE];
  u_int8_t Pn[TwoFish_BLOCK_SIZE];
  u_int8_t *p,*pout;
  u_int32_t i;


  if(size==TwoFish_BLOCK_SIZE)
    {

      if(!decrypt && tfdata->qBlockDefined)
	{   for(p=in,i=0;i<TwoFish_BLOCK_SIZE;i++,p++)
	    Pn[i]=*p ^ tfdata->qBlockCrypt[i];
	}
      else
	memcpy(Pn,in,TwoFish_BLOCK_SIZE);


      _TwoFish_BlockCrypt16(Pn,out,decrypt,tfdata);


      if(decrypt && tfdata->qBlockDefined)
        {	for (p=out,i=0;i<TwoFish_BLOCK_SIZE;i++,p++)
	    *p^=tfdata->qBlockPlain[i];
        }


      _TwoFish_qBlockPush(Pn,out,tfdata);
    }
  else
    {


      if(decrypt)
        {


	  _TwoFish_qBlockPop(CnMinusOne,PnMinusOne,tfdata);
	  _TwoFish_BlockCrypt16(CnMinusOne,CBCplusCprime,decrypt,tfdata);


	  for(p=in,pout=out,i=0;i<size;i++,p++,pout++)
	    *pout=*p ^ CBCplusCprime[i];


	  for(p=in,i=0;i<size;i++,p++)
	    CnMinusOne[i]=*p;
	  for(;i<TwoFish_BLOCK_SIZE;i++)
	    CnMinusOne[i]=CBCplusCprime[i];


	  _TwoFish_BlockCrypt16(CnMinusOne,PnMinusOne,decrypt,tfdata);

	  for(i=0;i<TwoFish_BLOCK_SIZE;i++)
	    PnMinusOne[i]=PnMinusOne[i] ^ tfdata->prevCipher[i];


	  _TwoFish_qBlockPush(CnMinusOne,PnMinusOne,tfdata);
	  _TwoFish_FlushOutput(tfdata->qBlockCrypt,TwoFish_BLOCK_SIZE,tfdata);
	  _TwoFish_FlushOutput(out,size,tfdata);
        }
      else
	{	_TwoFish_qBlockPop(PnMinusOne,CnMinusOne,tfdata);
	  memset(Pn,0,TwoFish_BLOCK_SIZE);
	  memcpy(Pn,in,size);
	  for(i=0;i<TwoFish_BLOCK_SIZE;i++)
	    Pn[i]^=CnMinusOne[i];
	  _TwoFish_BlockCrypt16(Pn,out,decrypt,tfdata);
	  _TwoFish_qBlockPush(Pn,out,tfdata);
	  _TwoFish_FlushOutput(tfdata->qBlockCrypt,TwoFish_BLOCK_SIZE,tfdata);
	  _TwoFish_FlushOutput(CnMinusOne,size,tfdata);
	}
      tfdata->qBlockDefined=FALSE;
    }
}
