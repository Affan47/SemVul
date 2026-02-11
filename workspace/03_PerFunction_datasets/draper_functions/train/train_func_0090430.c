ReadFami4(int w, uint8 ret)
{
 ret&=1;

 ret |= ((joy[2+w]>>(F4ReadBit[w]))&1)<<1;
 if(F4ReadBit[w]>=8) ret|=2;
 else F4ReadBit[w]++;

 return(ret);
}
