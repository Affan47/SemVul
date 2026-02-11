print (const char *name, const char *x)
{
	printIndent();
	if (x) {
		fprintf (file,"%s = \"%s\",\n",name,x);
	}
	else {
		fprintf (file,"%s\n",name);
	}
}
