dump(FILE *f, int pageNum)
{
  if (complexMode)
  {
    if (xml) dumpAsXML(f, pageNum);
    if (!xml) dumpComplex(f, pageNum);
  }
  else
  {
    fprintf(f,"<A name=%d></a>",pageNum);

    int listlen=HtmlOutputDev::imgList->getLength();
    for (int i = 0; i < listlen; i++) {
      GooString *fName= (GooString *)HtmlOutputDev::imgList->del(0);
      fprintf(f,"<IMG src=\"%s\"><br>\n",fName->getCString());
      delete fName;
    }
    HtmlOutputDev::imgNum=1;

    GooString* str;
    for(HtmlString *tmp=yxStrings;tmp;tmp=tmp->yxNext){
      if (tmp->htext){
		str=new GooString(tmp->htext);
		fputs(str->getCString(),f);
		delete str;
		fputs("<br>\n",f);
      }
    }
	fputs("<hr>\n",f);
  }
}
