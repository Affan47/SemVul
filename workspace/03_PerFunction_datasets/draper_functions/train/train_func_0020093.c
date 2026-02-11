copy_integer_array(int *a,int size)
{
int *b=(int *) malloc(size*sizeof(int));

	if (b==NULL){
	perror("malloc returned NULL");
	exit(1);
	}

int i;
	for(i=0;i<size;i++)
	{*(b+i)=*(a+i);}
return b;


}
