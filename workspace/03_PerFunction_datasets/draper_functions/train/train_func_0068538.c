insert_into_hash(hash_lex_struct *root, const char *name,
		      int len_from_begin, int index, int function)
{
  hash_lex_struct *end, *cur, *tails;

  if (!root->first_char)
  {
    root->first_char= -1;
    root->iresult= index;
    return;
  }

  if (root->first_char == -1)
  {
    int index2= root->iresult;
    const char *name2= (index2 < 0 ? sql_functions[-index2-1] :
			symbols[index2]).name + len_from_begin;
    root->first_char= (int) (uchar) name2[0];
    root->last_char= (char) root->first_char;
    tails= (hash_lex_struct*)malloc(sizeof(hash_lex_struct));
    root->char_tails= tails;
    tails->first_char= -1;
    tails->iresult= index2;
  }

  size_t real_size= (root->last_char-root->first_char+1);

  if (root->first_char>(*name))
  {
    size_t new_size= root->last_char-(*name)+1;
    if (new_size<real_size) printf("error!!!!\n");
    tails= root->char_tails;
    tails= (hash_lex_struct*)realloc((char*)tails,
				       sizeof(hash_lex_struct)*new_size);
    root->char_tails= tails;
    memmove(tails+(new_size-real_size),tails,real_size*sizeof(hash_lex_struct));
    end= tails + new_size - real_size;
    for (cur= tails; cur<end; cur++)
      cur->first_char= 0;
    root->first_char= (int) (uchar) *name;
  }

  if (root->last_char<(*name))
  {
    size_t new_size= (*name)-root->first_char+1;
    if (new_size<real_size) printf("error!!!!\n");
    tails= root->char_tails;
    tails= (hash_lex_struct*)realloc((char*)tails,
				    sizeof(hash_lex_struct)*new_size);
    root->char_tails= tails;
    end= tails + new_size;
    for (cur= tails+real_size; cur<end; cur++)
      cur->first_char= 0;
    root->last_char= (*name);
  }

  insert_into_hash(root->char_tails+(*name)-root->first_char,
		   name+1,len_from_begin+1,index,function);
}
