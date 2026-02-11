checktextype(char *p)
{
    if(strstr(p,"\\begin{")!=NULL ||
       strstr(p,"\\end{")!=NULL ||
       strstr(p,"\\underset")!=NULL ||
       strstr(p,"\\overset")!=NULL ||
       strstr(p,"\\displaystyle")!=NULL ||
       strstr(p,"\\mathcal")!=NULL) {
	textype=tt_latex; texname="latex";
    }
}
