scangetaddr(int Code,L9BYTE *Base,L9UINT32 *Pos,L9UINT32 acode,int *Mask)
{
	(*Mask)|=0x20;
	if (Code&0x20)
	{

		signed char diff=Base[*Pos];
		(*Pos)++;
		return (*Pos)+diff-1;
	}
	else
	{
		return acode+scanmovewa5d0(Base,Pos);
	}
}
