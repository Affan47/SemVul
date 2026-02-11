show()
{
 	int i;
  	for (i=0;i<level;i++)
  		printf("\t");
  	printf("[%d - %s] %s:%s\n",
 		level,gettypename().c_str(),skey.c_str(),svalue.c_str());

	if (child!=NULL)
		child->show();
 	if ( (type==JARRAY) || (type==JOBJECT) )
 	{
 		for (i=0;i<level;i++)
 			printf("\t");
 		printf("[/%s]\n",gettypename().c_str());
 	}

	if (sibling)
		sibling->show();
}
