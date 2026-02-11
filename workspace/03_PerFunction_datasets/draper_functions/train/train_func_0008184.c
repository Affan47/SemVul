collect_strings()
{
    long i;
    long ssize=last_text_nr()+1;
    int lsize=Thelanguages->length();
    The_Nilunparseitems=Nilunparseitems();
    string_collection=new unparseitems*[ssize];
    for( i=0; i<ssize;i++) {
	int j=0;
	string_collection[i]=new unparseitems[lsize];
	for(;j<lsize;j++)
	string_collection[i][j]=The_Nilunparseitems;
    }
    Theunparsedeclarations->unparse(v_null_printer, view_collect_strings);

}
