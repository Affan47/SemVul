parse_elf_header(FILE *file, struct elf_info *e_info )
{

	u32 entry_offset = 24;
	u32 p_off_offset = 28;
	u32 s_off_offset = 32;
	u16 p_num_offset = 44;
	u16 s_num_offset = 48;

	fseek( file, entry_offset, SEEK_SET );
	fread(&e_info->entry,sizeof(u32),1,file);

	fseek( file, p_off_offset, SEEK_SET );
	fread(&e_info->p_base,sizeof(u32),1,file);

	fseek( file, s_off_offset, SEEK_SET );
	fread(&e_info->s_base,sizeof(u32),1,file);

	fseek( file, p_num_offset, SEEK_SET );
	fread(&e_info->p_num,sizeof(u16),1,file);

	fseek( file, s_num_offset, SEEK_SET );
	fread(&e_info->s_num,sizeof(u16),1,file);

	printf("************************************\n");
	printf("entry          %lx \n",e_info->entry);
	printf("program header base %lu \n",e_info->p_base);
	printf("section header offset %lu \n",e_info->s_base);
	printf("program header num %lu \n",e_info->p_num);
	printf("section header num %lu \n",e_info->s_num);
	printf("************************************\n");

	if ( e_info->entry
		&& e_info->p_base
		&& e_info->s_base ){
		return true;
	}

	return false;
}
