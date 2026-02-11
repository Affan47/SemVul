resourcename(char *name,const char* prefix,const char* filename,int keepdot){
  const char* begin=name;
  const char* ptr;


  while(*prefix){
    *name++=*prefix++;
    }


  if((ptr=strrchr(filename,'/'))!=0) filename=ptr;
  if((ptr=strrchr(filename,'\\'))!=0) filename=ptr;


  while(*filename){


    if(*filename==':' || *filename=='_' || isalpha(*filename) || (isdigit(*filename) && (begin!=name))){
      *name++=*filename;
      }


    else if(*filename=='.'){
      if(!keepdot) break;
      *name++='_';
      }

    filename++;
    }
  *name=0;
  }
