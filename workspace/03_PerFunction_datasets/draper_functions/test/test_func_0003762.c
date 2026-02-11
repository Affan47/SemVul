commentline(char *line)
{
        int i;

        if(line[0] == '#') return TRUE;
        for(i=0;line[i]!='\n' && line[i]!=EOS;i++) {
                if(!isspace(line[i]))
			return FALSE;
        }
        return TRUE;
}
