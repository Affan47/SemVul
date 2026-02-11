isCubic(PointGroup* pointGroup)
{
	if(!strcmp(pointGroup->name,"Th")) return TRUE;
	if(!strcmp(pointGroup->name,"T")) return TRUE;
	if(!strcmp(pointGroup->name,"Td")) return TRUE;
	if(!strcmp(pointGroup->name,"O")) return TRUE;
	if(!strcmp(pointGroup->name,"Oh")) return TRUE;
	if(!strcmp(pointGroup->name,"I")) return TRUE;
	if(!strcmp(pointGroup->name,"Ih")) return TRUE;
	return FALSE;
}
