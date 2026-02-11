GetInfoType()
{
       	gchar *temp;
  	G_CONST_RETURN gchar *entrytext;

        if(Types==NULL || !strcmp(Types,_("Single Point")) )
        return;
        if(AddConical)
	{
       		gabedit_text_insert (GABEDIT_TEXT(text),NULL,NULL,NULL," Opt=Conical ",-1);
        	return;
	}

  	entrytext = gtk_entry_get_text(GTK_ENTRY(EntryTypes[0]));
	if(strcmp(entrytext,_("default"))) temp=g_strdup_printf("Opt(%s",entrytext);
	else temp=g_strdup_printf("Opt(");

  	entrytext = gtk_entry_get_text(GTK_ENTRY(EntryTypes[1]));
        if( strcmp(entrytext,_("default")) ) temp=g_strdup_printf("%s,%s",temp,entrytext);

  	entrytext = gtk_entry_get_text(GTK_ENTRY(EntryTypes[2]));
        if( strcmp(entrytext,_("default")) ) temp=g_strdup_printf("%s,MaxCycle=%s",temp,entrytext);

  	entrytext = gtk_entry_get_text(GTK_ENTRY(EntryTypes[3]));
        if( strcmp(entrytext,_("default")) ) temp=g_strdup_printf("%s,StepSize=%s",temp,entrytext);

  	entrytext = gtk_entry_get_text(GTK_ENTRY(EntryTypes[4]));
        if( strcmp(entrytext,_("No")) ) temp=g_strdup_printf("%s,Saddle=%s",temp,entrytext);

  	entrytext = gtk_entry_get_text(GTK_ENTRY(EntryTypes[5]));
        if( strcmp(entrytext,_("No")) ) temp=g_strdup_printf("%s,TS, noeigentest",temp);

        temp=g_strdup_printf("%s) ",temp);
	if(strstr(temp,"Opt()")) temp=g_strdup_printf("Opt ");
	if(strstr(temp,"Opt(,")) temp[4]=' ';

	gabedit_text_insert (GABEDIT_TEXT(text),NULL,NULL,NULL,"\n# ",-1);
       	gabedit_text_insert (GABEDIT_TEXT(text),NULL,NULL,NULL,temp,-1);

}
