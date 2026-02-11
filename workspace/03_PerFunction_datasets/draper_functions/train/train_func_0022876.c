searchScripts(char*code,Preferences*pref,Variable*vars,ThreadSync*scriptData)
{

	char*scriptName;
	int len=strlen(code);
	int pos=0,pos2;
	FILE*subFile;
	while(pos<len)
	{
		if(strncmp(&code[pos],"run(\"",4) == 0)
		{
			pos2=bracketFind(code,")",pos+4);
			if(pos2-pos<7 || code[pos2-1]!='\"')
			{
				pos++;
				continue;
			}
			scriptName=new char[pos2-pos-5];
			strcopy(scriptName,&code[pos+5],pos2-pos-6);
			bool newScript=true;
			for(int c=0; c<scriptData->subprogramPath.GetLen(); c++)
				if(strcmp(scriptData->subprogramPath[c],scriptName)==0)
				{
					newScript=false;
					break;
				}
			if(newScript)
			{
				struct stat fileStat;
				char*subFileContent;

				if(lstat(scriptName,&fileStat)!=0)
					;
				else {
					subFile=fopen(scriptName,"r");
					if(subFile==NULL || fileStat.st_size<=0)
						;
					else
					{
						subFileContent=new char[fileStat.st_size+1];
						subFileContent[fileStat.st_size]=(char)0;
						fread(subFileContent,fileStat.st_size,1,subFile);
						fclose(subFile);
						scriptData->subprogramPath.NewItem(scriptName);
						searchScripts(subFileContent,pref,vars,scriptData);
						delete[]subFileContent;
					}
				}
			}
			pos=pos2+1;
		}
		else pos++;
	}
}
