free_pattern(PATTERN_S **pattern)
{
    if(pattern && *pattern){
	free_pattern(&(*pattern)->next);
	if((*pattern)->substring)
	  fs_give((void **)&(*pattern)->substring);
	fs_give((void **)pattern);
    }
}
