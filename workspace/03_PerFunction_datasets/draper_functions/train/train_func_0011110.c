ocdumpnode(OCnode* node)
{
    if(node != NULL) {
        dumpocnode1(node,0);
    } else {
	fprintf(stderr,"<NULL>\n");
    }
    fflush(stderr);
}
