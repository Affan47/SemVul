main()

{

srandom(time(NULL));

int x=0;
printf("please enter array size");
scanf("%d",&x);

int *p =(int *) malloc(x*sizeof(int));


if (p==NULL){
perror("malloc returned NULL");
exit(1);
}

int i;
for(i=0; i<x; i++)
{
	*(p+i)=random();
}


int *q=copy_integer_array(p,x);
int *r=copy_integer_array(p,x);


int *iterator = q+(x-1);


sort_integer_array(q, iterator, 1);


int *iterator2 = r+(x-1);

sort_integer_array(r,iterator2,0);

for(i=0;i<x;i++){printf("\n%d\n",*(p+i));}
printf("\n");
for(i=0;i<x;i++){printf("\n%d\n",*(q+i));}
	printf("\n");
for(i=0;i<x;i++){printf("\n%d\n",*(r+i));}


free(p);
free(q);
free(r);


return 0;
}
