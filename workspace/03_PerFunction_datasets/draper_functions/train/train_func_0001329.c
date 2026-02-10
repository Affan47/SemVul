showAllFields(void){
  int i;
  cgi_printf("<font color=\"blue\">\n"
         "<p>Database fields:</p><ul>\n");
  for(i=0; i<nField; i++){
    cgi_printf("<li>aField[%d].zName = \"%h\";\n"
           "originally = \"%h\";\n"
           "currently = \"%h\"\";\n",(i),(aField[i].zName),(aField[i].zValue),(PD(aField[i].zName,"")));
    if( aField[i].zAppend ){
      cgi_printf("zAppend = \"%h\";\n",(aField[i].zAppend));
    }
    cgi_printf("mUsed = %d;\n",(aField[i].mUsed));
  }
  cgi_printf("</ul></font>\n");
}
