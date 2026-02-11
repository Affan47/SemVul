nclistunique(NClist* list)
{
    unsigned int i,j,k,len;
    ncelem* content;
    if(list == NULL || list->length == 0) return 1;
    len = list->length;
    content = list->content;
    for(i=0;i<len;i++) {
        for(j=i+1;j<len;j++) {
	    if(content[i] == content[j]) {

                for(k=j+1;k<len;k++) content[k-1] = content[k];
		len--;
	    }
	}
    }
    list->length = len;
    return 1;
}
