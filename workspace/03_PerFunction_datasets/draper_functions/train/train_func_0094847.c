print_array(a,datastart)
struct array *a;
void *datastart;
{ int k;
  int spots[100];
  int depth;
  char * spot;

  spot = datastart ? datastart : ((char*)a + a->datastart);

  if ( a->dim == 0 )
  {
    print_data_value(msg+strlen(msg),a->datatype,spot);
    strcat(msg,"\n");
    outstring(msg);
    return;
  }

  outstring("{");
  depth = 1;
  spots[depth] = 0;
  for (;;)
  { msg[0] = 0;
    if ( spots[depth] < a->sizes[depth-1] && depth < a->dim )
    { outstring("{"); depth++; spots[depth] = 0; continue; }
    if ( depth == a->dim )
    { for ( k = 0 ; k < a->sizes[depth-1] ; k++ )
      {
        print_data_value(msg+strlen(msg),a->datatype,spot);
        spot += a->itemsize;
        if ( k < a->sizes[depth-1] - 1 ) strcat(msg,",");
        if ( (strlen(msg) > 60) && (k < a->sizes[depth-1] - 1) )
        { outstring(msg);
          strcpy(msg,"\n ");
        }
      }
      outstring(msg);
    }
    outstring("}");
    depth--;
    if ( depth > 0 && (spots[depth]++ < a->sizes[depth-1]-1) )
    { int i;
      outstring(",\n");
      for ( i = 0 ; i < depth ; i++ ) outstring(" ");
    }
    if ( depth == 0 ) break;

    if ( breakflag ) break;
  }
  outstring("\n");
}
