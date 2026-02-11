ReadStateChunks(FILE *st, int32 totalsize)
{
 int t;
 uint32 size;
 int ret=1;

 while(totalsize > 0)
 {
  t=fgetc(st);
  if(t==EOF) break;
  if(!read32le(&size,st)) break;
  totalsize -= size + 5;

  switch(t)
  {
   case 1:if(!ReadStateChunk(st,SFCPU,size)) ret=0;break;
   case 2:if(!ReadStateChunk(st,SFCPUC,size)) ret=0;
          else
	  {
	   X.mooPI=X.P;
	  }
	  break;
   case 3:if(!ReadStateChunk(st,FCEUPPU_STATEINFO,size)) ret=0;break;
   case 4:if(!ReadStateChunk(st,FCEUCTRL_STATEINFO,size)) ret=0;break;
   case 5:if(!ReadStateChunk(st,FCEUSND_STATEINFO,size)) ret=0;break;
   case 0x10:if(!ReadStateChunk(st,SFMDATA,size)) ret=0;
	     break;
   default: if(fseek(st,size,SEEK_CUR)<0) goto endo;break;
  }
 }
 endo:
 return ret;
}
