expand_format(LM_mesh_struct *mesh, int kw_code, char *out_format)
{
	int i, j, duplicate_next = 0, size = 0;
	char *in_format = LM_kw_table[ kw_code ][2];

	out_format[0] = '\0';


	for(i=0;i<strlen(in_format);i++)
	{
		if( (in_format[i] == 'i') || (in_format[i] == 'r') )
		{
			if(!duplicate_next)
				duplicate_next = 1;

			for(j=1;j<=duplicate_next;j++)
			{
				strncat(out_format, &in_format[i], 1);
				size++;
			}

			duplicate_next = 0;
		}
		else if(in_format[i] == 'c')
		{
			strncat(out_format, &in_format[i], 1);
			size += 64;
		}
		else if(in_format[i] == 'd')
		{


			duplicate_next = mesh->dimension;
		}
		else if(in_format[i] == 's')
		{


			duplicate_next = mesh->sol_headers[ kw_code ][1];
		}
	}


	return(size);
}
