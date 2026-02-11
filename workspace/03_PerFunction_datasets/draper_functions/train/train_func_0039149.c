cJSONUtils_CompareToPatch(cJSON *patches,const char *path,cJSON *from,cJSON *to)
{
	if (from->type!=to->type)	{cJSONUtils_GeneratePatch(patches,"replace",path,0,to);	return;	}

	switch (from->type)
	{
	case cJSON_Number:
		if (from->valueint!=to->valueint || from->valuedouble!=to->valuedouble)
			cJSONUtils_GeneratePatch(patches,"replace",path,0,to);
		return;

	case cJSON_String:
		if (strcmp(from->valuestring,to->valuestring)!=0)
			cJSONUtils_GeneratePatch(patches,"replace",path,0,to);
		return;

	case cJSON_Array:
	{
		int c;char *newpath=(char*)malloc(strlen(path)+23);
		for (c=0,from=from->child,to=to->child;from && to;from=from->next,to=to->next,c++){
										sprintf(newpath,"%s/%d",path,c);	cJSONUtils_CompareToPatch(patches,newpath,from,to);
		}
		for (;from;from=from->next,c++)	{sprintf(newpath,"%d",c);	cJSONUtils_GeneratePatch(patches,"remove",path,newpath,0);	}
		for (;to;to=to->next,c++)		cJSONUtils_GeneratePatch(patches,"add",path,"-",to);
		free(newpath);
		return;
	}

	case cJSON_Object:
	{
		cJSON *a,*b;
		cJSONUtils_SortObject(from);
		cJSONUtils_SortObject(to);

		a=from->child,b=to->child;
		while (a || b)
		{
			int diff=(!a)?1:(!b)?-1:cJSONUtils_strcasecmp(a->string,b->string);
			if (!diff)
			{
				char *newpath=(char*)malloc(strlen(path)+cJSONUtils_PointerEncodedstrlen(a->string)+2);
				cJSONUtils_PointerEncodedstrcpy(newpath+sprintf(newpath,"%s/",path),a->string);
				cJSONUtils_CompareToPatch(patches,newpath,a,b);
				free(newpath);
				a=a->next;
				b=b->next;
			}
			else if (diff<0)	{cJSONUtils_GeneratePatch(patches,"remove",path,a->string,0);	a=a->next;}
			else				{cJSONUtils_GeneratePatch(patches,"add",path,b->string,b);		b=b->next;}
		}
		return;
	}

	default:			break;
	}
}
