NormalRestore(void)
{
	GameState temp;
	int Bytes;
#ifdef L9DEBUG
	printf("function - restore");
#endif
	if (Cheating)
	{

		Cheating=FALSE;
		error("\rWord is: %s\r",ibuff);
	}

	if (os_load_file((L9BYTE*) &temp,&Bytes,sizeof(GameState)))
	{
		if (Bytes==V1FILESIZE)
		{
			printstring("\rGame restored.\r");
			memset(workspace.listarea,0,LISTAREASIZE);
			memmove(workspace.vartable,&temp,V1FILESIZE);
		}
		else if (CheckFile(&temp))
		{
			printstring("\rGame restored.\r");

			memmove(workspace.vartable,temp.vartable,sizeof(SaveStruct));
		}
		else
		{
			printstring("\rSorry, unrecognised format. Unable to restore\r");
		}
	}
	else printstring("\rUnable to restore game.\r");
}
