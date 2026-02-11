matrix_print( struct matrix *m, const char *a, const char *b )
{
	int i,j;

	if(b) printf("     ");

	if(a) for(i=0;i<m->width;i++) printf("    %c",a[i]);

	printf("\n");

	for(j=0;j<=m->height;j++) {
		if(b) {
			if(j>0) {
				printf("%c ",b[j-1]);
			} else {
				printf("  ");
			}
		}

		for(i=0;i<=m->width;i++) {
			char t = matrix(m,i,j).traceback;
			if(t==0) t=' ';
			printf("%3d%c ",matrix(m,i,j).score,t);
		}
		printf("\n");
	}

}
