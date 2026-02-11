set_scope(depth)
int depth;
{ int oldsymtop = symtop;
  symdepth = depth-1;
  if ( symdepth > 0 )
    symtop = symsave[symdepth-1];
  else symtop = 0;
  if ( oldsymtop > symtop )
     memset((char*)(symtable+symtop),0,(oldsymtop-symtop)*sizeof(struct sym));
}
